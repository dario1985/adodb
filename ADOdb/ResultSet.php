<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * Resultset Class
 */
class ResultSet implements \Serializable,
                           \IteratorAggregate
{
    protected $cache = null;
    protected $statement = null;

    /* Publically accessible row values */
    protected $fields = false;
    protected $timeCreated;
    protected $EOF = false;
    protected $numOfRows = null;
    protected $bufferedResults = null;

    protected $publicProperties = array(
        'fields',
        'EOF'
    );

    public function __construct(Statement $statement)
    {
        $this->timeCreated = time();
        $this->statement = $statement;
        $this->canSeek = $statement->canSeek();
        $this->currentRow = -1;
        $this->moveNext();
    }

    public function __destruct()
    {
        if ($this->statement) {
            $this->statement->closeCursor();
            $this->statement = null;
        }
    }

    public function __get($name)
    {
        if (in_array($name, $this->publicProperties)) {
            return $this->$name;
        }
    }

    /**
     * Interface
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
    public function recordCount()
    {
        if ($this->numOfRows === null) {
            $this->numOfRows = $this->statement->rowCount();
        }
        return $this->numOfRows;
    }

    public function currentRow()
    {
        return $this->currentRow;
    }

    /**
     * Some databases allow multiple recordsets to be returned. This function
     * will return true if there is a next recordset, or false if no more.
     */
    public function NextRecordSet()
    {
        return $this->statement->nextRowset();
    }

    /**
     * Move to the first row in the recordset.
     * Many databases do NOT support this.
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
        if ($this->numOfRows > 0)
            return $this->Move($this->numOfRows - 2);

        /* Compat?

        if ($this->EOF)
            return false;

        while (!$this->EOF) {
            $f = $this->fields;
            $this->MoveNext();
        }
        $this->fields = $f;
        $this->EOF = false;
        return true;
        */
    }

    /**
     * MoveNext: Fetch next row and check if we're at the end
     */
    public function MoveNext()
    {
        if (!$this->EOF) {
            if ($this->recordCount() > ++$this->currentRow) {
                $this->fields = $this->statement->fetch();
                return true;
            } else {
                $this->fields = false;
                $this->EOF = true;
            }
        } else {
            return false;
        }
    }

    /**
     * Random access to a specific row in the recordset.
     * Some databases do not support
     * access to previous rows in the databases (no scrolling backwards).
     *
     * @param rowNumber is the row to move to (0-based)
     *
     * @return true if there still rows available,
     *         or false if there are no more rows (EOF).
     */
    public function Move($rowNumber = 0)
    {
        $this->EOF = false;

        if ($this->numOfRows > 0 && $rowNumber >= $this->numOfRows) {
            $rowNumber = $this->numOfRows - 2; // Overflow to last record
        }

        if ($rowNumber == $this->currentRow) {
            return true;
        }

        if ($this->canSeek) {
            $fields = $this->statement->fetch($rowNumber);
        } else {
            if ($this->bufferedResults === null) {
                $this->bufferedResults = new ArrayIterator(
                    $this->statement->fetchAll()
                );
            }
            $fields = $this->bufferedResults[$rowNumber];
        }

        if ($fields) {
            $this->fields = $fields;
            $this->currentRow = $rowNumber;
            return true;
        }

        $this->fields = false;
        $this->EOF = true;
        return false;
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
     * @return the number of columns in the recordset.
     * Some databases will set this to 0
     * if no records are returned, others will return
     * the number of columns in the query.
     */
    public function FieldCount()
    {
        if ($this->numOfFields === null) {
            $this->numOfFields = $this->statement->columnCount();
        }
        return $this->numOfFields;
    }

    /**
     * Serialize
     */
    public function serialize()
    {
            return serialize($this);
    }

    /**
     * Unserialize
     */
    public function unserialize($data)
    {
            return unserialize($data);
    }
}
