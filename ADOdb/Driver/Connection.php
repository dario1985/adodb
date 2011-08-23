<?php

namespace ADOdb\Driver;

/**
* Connection and query wrapper
*/
interface Connection
{
	/**
	* Connect: Establish connection to a database
	* @param host String
	* @param user String [optional]
	* @param pass String [optional]
	* @param database String [optional]
	*/	
    public function Connect($host, $user='', $pass='', $database='');

	/**
	* Insert_ID: Retrieve the ID of the last insert operation
	* @return String containing last insert ID
	*/
	public function Insert_ID();

	/**
	* GetAll: Retrieve an array of results from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	public function GetAll($sql, $vars=null);

	/**
	* CacheGetAll: Wrapper to emulate cached GetAll
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of results
	*/
	public function CacheGetAll($timeout, $sql, $vars=null);

	/**
	* Execute: Retrieve a resultset from a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	public function Execute($sql, $vars=null);

	/**
	* CacheExecute: Wrapper to emulate cached Execute
	* @param timeout int count of seconds for cache expiry
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return ADODB_PDO_ResultSet object
	*/
	public function CacheExecute($timeout, $sql, $vars=null);

	/**
	* Affected_Rows: Retrieve the number of rows affected by Execute
	* @return The number of affected rows
	*/
	public function Affected_Rows();

	/**
	* GetRow: Retrieve the first row of a query result
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of data from first result
	*/
	public function GetRow($sql, $vars=null);

	/**
	* GetOne: Retrieve the first value in the first row of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return String data of the requested value
	*/
	public function GetOne($sql, $vars=null);

	/**
	* GetAssoc: Retrieve data from a query mapped by value of first column
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of mapped data
	*/
	public function GetAssoc($sql, $vars=null);

	/**
	* GetCol: Retrieve the values of the first column of a query
	* @param sql String query to execute
	* @param vars Array of variables to bind [optional]
	* @return Array of column data
	*/
	public function GetCol($sql, $vars=null);

	/**
	* MetaColumns: Retrieve information about a table's columns
	* @param table String name of table to find out about
	* @return Array of ADODB_PDO_FieldData objects
	*/
	public function MetaColumns($table);

}
