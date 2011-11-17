<?php

namespace ADOdb\Driver\PDO;

use \PDO as PDO,
    ADOdb\Connection as ADODB_Connection,
    ADOdb\Driver\PDO\FieldObject as ADODB_PDO_FieldObject,
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
    protected $dsn;
    protected $connector;
    protected $hostname;
    protected $username;
    protected $password;

    public $database;

    /** Debug flag, publically accessible */
    public $debug;

    /** PDO demands fetchmodes on each resultset, so define a default */
    protected $fetchmode;

    /** Number of rows affected by the last Execute */
    protected $affected_rows;

    /** PDO drivers options:

     * This array holds one or more key=>value pairs to set attribute values
     * for the PDOStatement object that this method returns. You would most
     * commonly use this to set the PDO::ATTR_CURSOR value to PDO::CURSOR_SCROLL
     * to request a scrollable cursor. Some drivers have driver specific options
     * that may be set at prepare-time.
     */
    protected $pdoDriverOptions = array();

    /**
     * Constructor: Initialise connector
     * @param connector String denoting type of database
     */
    public function __construct($connector = 'mysql')
    {
        if ($connector instanceof \ADOdb\DataSource) {
            $this->connector = $connector->getType();
            $this->hostname = $connector->getHostname();
            $this->username = $connector->getUsername();
            $this->password = $connector->getPassword();
            $this->database = $connector->getDatabase();
            $this->pdoDriverOptions = $connector->getOptions();
        } else {
            $this->connector = $connector;
        }
    }

    /**
     * Connect: Establish connection to a database
     * @param host String [optional]
     * @param user String [optional]
     * @param pass String [optional]
     * @param database String [optional]
     */
    public function Connect($hostname = null,
                            $username = null,
                            $password = null,
                            $database = null,
                            $driverOptions = null)
    {
        if ($hostname) $this->hostname = $hostname;
        if ($username) $this->username = $username;
        if ($password) $this->password = $password;
        if ($database) $this->database = $database;

        if ($driverOptions && is_array($driverOptions)) {
            $this->pdoDriverOptions = array_merge(
                $this->pdoDriverOptions,
                $driverOptions
            );
        }

        $this->dsn = $this->connector
            . ':host=' . $this->hostname
            . ';dbname=' . $this->database;

        $db = new PDO(
            $this->dsn,
            $this->username,
            $this->password
        );

        if ($this->pdoDriverOptions && is_array($this->pdoDriverOptions)) {
            foreach ($this->pdoDriverOptions as $attr => &$value) {
                $db->setAttribute($attr, $value);
            }
        }

        $this->pdoDriverOptions = array(
            PDO::ATTR_CURSOR => PDO::CURSOR_SCROLL
        );

        $this->fetchmode = self::FETCH_ASSOC;
        $this->_db = $db;
    }

    /**
     * SetFetchMode: Change the fetch mode of future resultsets
     * @param fm Integer specified by constant
     */
    public function setFetchMode($fm)
    {
        $this->fetchmode = $fm;
    }

    public function setAttribute($attribute, $value = null)
    {
        $this->pdoDriverOptions[$attribute] = $value;
        if ($this->_db) {
            $this->_db->setAttribute($attribute, $value);
        }
    }

    public function getAttribute($attribute)
    {
        return $this->pdoDriverOptions[$attribute];
    }

    public function canScroll()
    {
        return ($this->getAttribute(PDO::ATTR_CURSOR) == PDO::CURSOR_SCROLL);
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
        $st = $this->pdoQuery($sql, $vars);
        return $st ? $st->fetchAll() : false;
    }

    /**
     * Execute: Retrieve a resultset from a query
     * @param sql String query to execute
     * @param vars Array of variables to bind [optional]
     * @return ADODB_PDO_ResultSet object
     */
    public function Execute($sql, $vars=null)
    {
        $st = $this->pdoQuery($sql, $vars);
        $this->affected_rows = $st->rowCount();
        return $st ? new ADODB_PDO_ResultSet($st) : false;
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
        $st = $this->pdoQuery($sql, $vars);
        return $st ? $st->fetch() : false;
    }

    /**
     * GetOne: Retrieve the first value in the first row of a query
     * @param sql String query to execute
     * @param vars Array of variables to bind [optional]
     * @return String data of the requested value
     */
    public function GetOne($sql, $vars=null)
    {
        $st = $this->pdoQuery($sql, $vars);
        return $st ? $st->fetchColumn() : false;
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
        $st = $this->pdoQuery($sql, $vars);

        if ($st) {
            if ($st->columnCount() > 2) {
                while ($row = $st->fetch()) {
                    $rowidx = array_shift($row);
                    $out[$rowidx] = $row;
                }
            } else if ($st->columnCount == 2) {
                while ($row = $st->fetch()) {
                    $rowidx = array_shift($row);
                    $out[$rowidx] = array_shift($row);
                }
            } else {
                $out = false;
            }
        } else {
            $out = false;
        }
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
        $st = $this->pdoQuery($sql, $vars);

        if ($st) {
            while ($val = $st->fetchColumn())
                $out[] = $val;
            return $out;
        } else {
            return false;
        }
    }

    /**
     * MetaColumns: Retrieve information about a table's columns
     * @param table String name of table to find out about
     * @return Array of ADODB_PDO_FieldObject objects
     */
    public function MetaColumns($table)
    {
        $out = array();

        $st = $this->pdoQuery('select * from ' . $table);
        for ($i = 0; $i < $st->columnCount(); $i++)
            $out[] = new ADODB_PDO_FieldObject($st->getColumnMeta($i));

        return $out;
    }

    /**
     * pdoQuery: Private helper function for Get*
     * @param sql String query to execute
     * @param vars Array of variables to bind [optional]
     * @return PDOStatement object of results, or false on fail
     */
    protected function pdoQuery($sql, $vars=null)
    {
        $st = $this->_db->prepare(
                $sql, $this->pdoDriverOptions
        );
        $st->setFetchMode($this->fetchmode);
        if (!is_array($vars))
            $vars = array($vars);
        return $st->execute($vars) ? $st : false;
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
