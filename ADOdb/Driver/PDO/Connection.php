<?php

namespace ADOdb\Driver\PDO;

use \PDO as PDO,
    ADOdb\Connection as ADODB_Connection,
    ADOdb\Driver\PDO\FieldData as ADODB_PDO_FieldData,
    ADOdb\Driver\PDO\ResultSet as ADODB_PDO_ResultSet;

/**
* Connection and query wrapper
*/
class Connection extends ADODB_Connection
{
    const FETCH_NUM = PDO::FETCH_NUM;
    const FETCH_ASSOC = PDO::FETCH_ASSOC;

	/** PDO connection to wrap */
	protected $_db;
	
	/** Connection information (database name is public) */
	protected $connector;
	protected $dsn;
	protected $host;
	protected $user;
	protected $pass;

	public $database;
	
	/** Debug flag, publically accessible */
	public $debug;
	
	/** PDO demands fetchmodes on each resultset, so define a default */
	protected $fetchmode;

	/** Number of rows affected by the last Execute */
	protected $affected_rows;
	
	/**
	* Constructor: Initialise connector
	* @param connector String denoting type of database
	*/
	public function __construct($connector='mysql')
	{
		$this->connector = $connector;
	}
	
	/**
	* Connect: Establish connection to a database
	* @param host String
	* @param user String [optional]
	* @param pass String [optional]
	* @param database String [optional]
	*/
	public function Connect($host, $user='', $pass='', $database='')
	{
		$this->host = $host;
		$this->user = $user;
		$this->pass = $pass;
		$this->database = $database;

		switch($this->connector)
		{
			case 'mysql':
				$this->dsn = sprintf('%s:host=%s;dbname=%s',
					$this->connector,
					$this->host,
					$this->database);
				$this->_db = new PDO($this->dsn, $this->user, $this->pass);
				$this->_db->setAttribute(PDO::MYSQL_ATTR_USE_BUFFERED_QUERY, true);
				$this->fetchmode = self::FETCH_ASSOC;
				break;
		}
	}

	/**
	* SetFetchMode: Change the fetch mode of future resultsets
	* @param fm Integer specified by constant
	*/
	public function SetFetchMode($fm)
	{
		$this->fetchmode = $fm;
	}

	/**
	* Insert_ID: Retrieve the ID of the last insert operation
	* @return String containing last insert ID
	*/
	public function Insert_ID()
	{
		return $this->_db->lastInsertId();
	}

	/**
	* GetAll: Retrieve an array of results from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	public function GetAll($sql, $vars=null)
	{
		$st = $this->DoQuery($sql, $vars);
		return $st?$st->fetchAll():false;
	}

	/**
	* CacheGetAll: Wrapper to emulate cached GetAll
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	public function CacheGetAll($timeout, $sql, $vars=null)
	{
		return $this->GetAll($sql, $vars);
	}

	/**
	* Execute: Retrieve a resultset from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	public function Execute($sql, $vars=null)
	{
		$st = $this->DoQuery($sql, $vars);
		$this->affected_rows = $st->rowCount();
		return $st ? new ADODB_PDO_ResultSet($st):false;
	}

	/**
	* CacheExecute: Wrapper to emulate cached Execute
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	public function CacheExecute($timeout, $sql, $vars=null)
	{
		return $this->Execute($sql, $vars);
	}

	/**
	* Affected_Rows: Retrieve the number of rows affected by Execute
	* @return The number of affected rows
	*/
	public function Affected_Rows()
	{
		return $this->affected_rows;
	}

	/**
	* GetRow: Retrieve the first row of a query result
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of data from first result
	*/
	public function GetRow($sql, $vars=null)
	{
		$st = $this->DoQuery($sql, $vars);
		return $st?$st->fetch():false;
	}

	/**
	* GetOne: Retrieve the first value in the first row of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return String data of the requested value
	*/
	public function GetOne($sql, $vars=null)
	{
		$st = $this->DoQuery($sql, $vars);
		return $st?$st->fetchColumn():false;
	}

	/**
	* GetAssoc: Retrieve data from a query mapped by value of first column
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of mapped data
	*/
	public function GetAssoc($sql, $vars=null)
	{
		$out = array();
		$st = $this->DoQuery($sql, $vars);

		if($st)
		{
			if($st->columnCount() > 2)
			{
				while($row = $st->fetch())
				{
					$rowidx = array_shift($row);
					$out[$rowidx] = $row;
				}
			}
			else if($st->columnCount == 2)
			{
				while($row = $st->fetch())
				{
					$rowidx = array_shift($row);
					$out[$rowidx] = array_shift($row);
				}
			}
			else $out = false;
		}
		else $out = false;
		return $out;
	}

	/**
	* GetCol: Retrieve the values of the first column of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of column data
	*/
	public function GetCol($sql, $vars=null)
	{
		$out = array();
		$st = $this->DoQuery($sql, $vars);

		if($st)
		{
			while($val = $st->fetchColumn()) $out[] = $val;
			return $out;
		}
		else return false;
	}

	/**
	* MetaColumns: Retrieve information about a table's columns
	* @param table String name of table to find out about
	* @return Array of ADODB_PDO_FieldData objects
	*/
	public function MetaColumns($table)
	{
		$out = array();
		
		$st = $this->DoQuery('select * from '.$table);
		for($i=0; $i<$st->columnCount(); $i++)
			$out[] = new ADODB_PDO_FieldData($st->getColumnMeta($i));

		return $out;
	}
	
	/**
	* DoQuery: Private helper function for Get*
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return PDOStatement object of results, or false on fail
	*/
	private function DoQuery($sql, $vars=null)
	{
		$st = $this->_db->prepare($sql);
		$st->setFetchMode($this->fetchmode);
		if(!is_array($vars)) $vars = array($vars);
		return $st->execute($vars)?$st:false;
	}

	/**
	* qstr: Quote a string for use in database queries
	* @param in String parameter to quote
	* @return String quoted by database
	*/
	public function qstr($in)
	{
		return $this->_db->quote($in);
	}
	
	/**
	* quote: Quote a string for use in database queries
	* @param in String parameter to quote
	* @return String quoted by database
	*/
	public function quote($in)
	{
		return $this->_db->quote($in);
	}
}
