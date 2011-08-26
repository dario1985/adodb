<?php

namespace ADOdb\Driver;

interface ResultSet extends \Iterator
{
	/**
	* RecordCount: Retrieve number of records in this RS
	* @return Integer number of records
	*/
	public function RecordCount();

	/**
	* MoveNext: Fetch next row and check if we're at the end
	*/
	public function MoveNext();
}

