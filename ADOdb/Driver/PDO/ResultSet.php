<?php

namespace ADOdb\Driver\PDO;

use ADOdb\ResultSet as ADODB_Resultset;

/**
* Resultset PDO
*/
class ResultSet extends ADODB_Resultset
{
	/** PDO resultset to wrap */
	protected $_st;
	
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
}
