<?php

namespace ADOdb;

use ADOdb\Driver\ResultSet as DriverResultSet;

/**
* Resultset wrapper
*/
abstract class ResultSet implements DriverResultSet
{
	/** One-time resultset information */
	protected $results;
	protected $rowcount;
	protected $cursor;

	/** Publically accessible row values */
	public $fields;

	/** Public end-of-resultset flag */
	public $EOF;

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
	        if ($this->cursor < $this->rowcount) {
		    $this->EOF = false;
		    $this->next();
		    $this->cursor++;
	        } else {
        	    $this->EOF = true;
	            $this->fields = array();
	        }
	}
}
