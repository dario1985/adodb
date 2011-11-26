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
class ResultSet implements \Countable, 
                           \IteratorAggregate
{

    /**
     * Cache Driver
     * @var Cache
     */
    protected $cache = null;
    
    /**
     * Statement object
     * @var Statement
     */
    protected $statement = null;

    /* Publically accessible  __get() attributes: see $publicProperties */
    protected $fields = false;
    protected $timeCreated;
    protected $EOF = false;
    protected $numOfRows = null;
    protected $numOfFields = null;
    
    protected $bufferedResults = null;
    
    protected $publicProperties = array(
        'timeCreated' => 1,
        'numOfFields' => 1,
        'numOfRows' => 1,
        'fields' => 1,
        'EOF' => 1
    );

    public function __construct(Statement $statement)
    {
        $this->statement = $statement;
        $this->timeCreated = $statement->timeCreated();
        $this->canSeek = $statement->canSeek();
        $this->numOfRows = $statement->rowCount();
        $this->numOfFields = $statement->columnCount();
        $this->currentRow = -1;
        $this->moveNext();
    }

    public function __destruct()
    {
        if ($this->statement !== null) {
            $this->statement->close();
            $this->statement = null;
        }
    }

    public function __get($name)
    {
        if (isset($this->publicProperties[$name])) {
            return $this->$name;
        }
    }

    /**
     * RecordCount: Retrieve number of records in this RS
     * @return Integer number of records
     */
    public function recordCount()
    {
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
    public function nextRecordSet()
    {
        return $this->statement->nextRowset();
    }

    /**
     * Move to the first row in the recordset.
     * Many databases do NOT support this.
     *
     * @return boolean
     */
    public function moveFirst()
    {
        if ($this->currentRow === 0) {
            return true;
        }
        return $this->move(0);
    }

    /**
     * Move to the last row in the recordset.
     *
     * @return boolean
     */
    public function moveLast()
    {
        if ($this->numOfRows > 0)
            return $this->move($this->numOfRows - 2);

        if ($this->EOF)
            return false;
    }

    /**
     * MoveNext: Fetch next row and check if we're at the end
     */
    public function moveNext()
    {
        if (!$this->EOF && $this->numOfRows > ++$this->currentRow) {
            if ($this->bufferedResults === null) {
                $this->fields = $this->statement->fetch();
            } else {
                $this->fields = $this->bufferedResults[$this->currentRow];
            }
            return true;
        } else {
            $this->fields = false;
            $this->EOF = true;
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
    public function move($rowNumber = 0)
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
                $this->bufferedResults = $this->statement->fetchAll();
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
    public function fields($colname)
    {
        return $this->fields[$colname];
    }

    /**
     * Get the FieldObjects of all columns in an array.
     *
     */
    public function fieldTypesArray()
    {
        $fields = array();
        for ($i = 0, $max = $this->fieldCount(); $i < $max; $i++) {
            $fields[] = $this->fetchField();
        }
        return $fields;
    }
    
    public function fetchField($column_number = 0)
    {
        $field = $this->statement->getColumnMeta($column_number);
        if ($field !== false) {
            return $field;
        } else {
            throw new \Exception('Driver don\'t support Column Meta Data');
        }
    }

    /**
     * @return the number of columns in the recordset.
     * Some databases will set this to 0
     * if no records are returned, others will return
     * the number of columns in the query.
     */
    public function fieldCount()
    {
        return $this->numOfFields;
    }
    
    /*
     * IteratorAggregate Interface
     */
    
    /**
     * Return ResultSetIterator
     * @return RecordsetIterator
     */
    public function getIterator()
    {
        return new ResultsetIterator($this);
    }
    
    /*
     * Countable Interface
     */
    
    /**
     * Return RecordCount
     * @return int Row Count
     */
    public function count()
    {
        return $this->numOfRows;
    }
}