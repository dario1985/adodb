<?php

namespace ADOdb;

use ADOdb\Driver\ResultSet as DriverResultSet;

/**
 * Resultset
 */
abstract class ResultSet implements DriverResultSet,
                                    \Serializable
{

    /** One-time resultset information */
    protected $numOfRows = 0;
    protected $numOfFields = 0;
    protected $currentRow = -1;
    protected $canSeek = true;

    /** Publically accessible row values */
    public $fields = false;
    public $timeCreated;

    /** Public end-of-resultset flag */
    public $EOF = false;

    public function __construct()
    {
        $this->timeCreated = time();
    }

    public function __destruct()
    {
        $this->Close();
    }

    /**
     * Fetch a specific row in the recordset. Some databases do not support
     * access to previous rows in the databases (no scrolling backwards).
     *
     * @param rowNumber is the row to move to (0-based)
     */
    abstract protected function fetchRow($rowNumber = 0);

    /**
     * @return RecordsetIterator 
     */
    public function getIterator()
    {
        return new ResultsetIterator($this);
    }

    /**
     * RecordCount: Retrieve number of records in this RS
     * @return Integer number of records
     */
    public function RecordCount()
    {
        return $this->numOfRows;
    }

    /**
     * @return the current row in the recordset. If at EOF, will return the last row. 0-based.
     */
    public function CurrentRow()
    {
        return $this->currentRow;
    }

    /*
     * Some databases allow multiple recordsets to be returned. This function
     * will return true if there is a next recordset, or false if no more.
     */

    public function NextRecordSet()
    {
        return false;
    }

    /**
     * Move to the first row in the recordset. Many databases do NOT support this.
     *
     * @return true or false
     */
    public function MoveFirst()
    {
        if ($this->currentRow == 0)
            return true;
        return $this->Move(0);
    }

    /**
     * Move to the last row in the recordset. 
     *
     * @return true or false
     */
    public function MoveLast()
    {
        if ($this->numOfRows >= 0)
            return $this->Move($this->numOfRows - 1);
        if ($this->EOF)
            return false;
        while (!$this->EOF) {
            $f = $this->fields;
            $this->MoveNext();
        }
        $this->fields = $f;
        $this->EOF = false;
        return true;
    }

    /**
     * MoveNext: Fetch next row and check if we're at the end
     */
    public function MoveNext()
    {
        if (!$this->EOF) {
            if ($this->numOfRows > ++$this->currentRow) {
                $this->fields = $this->fetchRow($this->currentRow);
                return true;
            } else {
                $this->fields = false;
                $this->EOF = true;
            }
        } else
            return false;
    }

    /**
     * Random access to a specific row in the recordset. Some databases do not support
     * access to previous rows in the databases (no scrolling backwards).
     *
     * @param rowNumber is the row to move to (0-based)
     *
     * @return true if there still rows available, or false if there are no more rows (EOF).
     */
    public function Move($rowNumber = 0)
    {
        $this->EOF = false;
        if ($rowNumber == $this->currentRow)
            return true;

        if ($this->canSeek) {
            $fields = $this->fetchRow($rowNumber);
            if ($fields) {
                $this->fields = $fields;
                $this->currentRow = $rowNumber;
                return true;
            } else {
                $this->fields = false;
                $this->EOF = true;
                return false;
            }
        } else {
            throw new Exception('Seek feature not supported');
        }
    }

    /**
     * Get the value of a field in the current row by column name.
     * Will not work if ADODB_FETCH_MODE is set to ADODB_FETCH_NUM.
     * 
     * @param colname  is the field to access
     *
     * @return the value of $colname column
     */
    public function Fields($colname)
    {
        return $this->fields[$colname];
    }

    /**
     * Get the ADOFieldObjects of all columns in an array.
     *
     */
    public function FieldTypesArray()
    {
        $arr = array();
        for ($i=0, $max=$this->numOfFields; $i < $max; $i++) {
            $arr[] = $this->FetchField($i);
    }
        return $arr;
    }

    /**
     * @return the number of columns in the recordset. Some databases will set this to 0
     * if no records are returned, others will return the number of columns in the query.
     */
    public function FieldCount() 
    {
        return $this->numOfFields;
    }   

    public function serialize()
    {
    }

    public function unserialize($data)
    {
    }
}
