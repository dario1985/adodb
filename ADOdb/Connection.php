<?php

namespace ADOdb;

use ADOdb\Driver\Connection as DriverConnection;

/**
* Connection and query wrapper
*/
abstract class Connection implements DriverConnection
{
	
    /**
    * NewADOConnection: Thin wrapper to generate a new ADODB_Connection object
    * @param connector String denoting type of database
    * @return ADODB_PDO object
    */
    static public function NewADOConnection($connector)
    {
        switch ($connector) {
            default:
    	    return new ADOdb\Datasources\PDO\Connection($connector);
        }
    }

    /**
	* Constructor: Initialise connector
	* @param connector String denoting type of database
	*/
	public function __construct($connector);
	
	/**
	* Connect: Establish connection to a database
	* @param host String
	* @param user String [optional]
	* @param pass String [optional]
	* @param database String [optional]
	*/	
    abstract public function Connect($host, $user='', $pass='', $database='');

	/**
	* Insert_ID: Retrieve the ID of the last insert operation
	* @return String containing last insert ID
	*/
	abstract public function Insert_ID();

	/**
	* GetAll: Retrieve an array of results from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	abstract public function GetAll($sql, $vars=null);

	/**
	* CacheGetAll: Wrapper to emulate cached GetAll
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	abstract public function CacheGetAll($timeout, $sql, $vars=null);

	/**
	* Execute: Retrieve a resultset from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	abstract public function Execute($sql, $vars=null);

	/**
	* CacheExecute: Wrapper to emulate cached Execute
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	abstract public function CacheExecute($timeout, $sql, $vars=null);

	/**
	* Affected_Rows: Retrieve the number of rows affected by Execute
	* @return The number of affected rows
	*/
	abstract public function Affected_Rows();

	/**
	* GetRow: Retrieve the first row of a query result
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of data from first result
	*/
	abstract public function GetRow($sql, $vars=null);

	/**
	* GetOne: Retrieve the first value in the first row of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return String data of the requested value
	*/
	abstract public function GetOne($sql, $vars=null);

	/**
	* GetAssoc: Retrieve data from a query mapped by value of first column
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of mapped data
	*/
	abstract public function GetAssoc($sql, $vars=null);

	/**
	* GetCol: Retrieve the values of the first column of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of column data
	*/
	abstract public function GetCol($sql, $vars=null);

	/**
	* MetaColumns: Retrieve information about a table's columns
	* @param table String name of table to find out about
	* @return Array of ADODB_PDO_FieldData objects
	*/
	abstract public function MetaColumns($table);

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
