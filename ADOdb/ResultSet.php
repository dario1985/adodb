<?php

namespace ADOdb;

use ADOdb\Driver\ResultSet as DriverResultSet;

/**
* Resultset wrapper
*/
class ResultSet implements DriverResultSet;
{
	/** PDO resultset to wrap */
	protected $_st;
	
	/** One-time resultset information */
	protected $results;
	protected $rowcount;
	protected $cursor;

	/** Publically accessible row values */
	public $fields;

	/** Public end-of-resultset flag */
	public $EOF;

	/**
	* Constructor: Initialise resultset and first results
	* @param st PDOStatement object to wrap
	*/
	public function __construct($st)
	{
		$this->_st = $st;
		$this->results = $st->fetchAll();
		$this->rowcount = count($this->results);
		$this->cursor = 0;
		$this->MoveNext();
	}

	/**
	* RecordCount: Retrieve number of records in this RS
	* @return Integer number of records
	*/
	public function RecordCount()
	{
		return $this->rowcount;
	}

	/**
	* MoveNext: Fetch next row and check if we're at the end
	*/
	public function MoveNext()
	{
		$this->fields = $this->results[$this->cursor++];
		$this->EOF = ($this->cursor == $this->rowcount) ? 1 : 0;
	}
}
