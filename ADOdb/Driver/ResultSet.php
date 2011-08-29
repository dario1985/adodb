<?php

namespace ADOdb\Driver;

interface ResultSet extends \IteratorAggregate
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

    /*
     * Some databases allow multiple recordsets to be returned. This function
     * will return true if there is a next recordset, or false if no more.
     */
    public function NextRecordSet();

    /**
     * Move to the first row in the recordset. Many databases do NOT support this.
     *
     * @return true or false
     */
    public function MoveFirst();

    /**
     * Move to the last row in the recordset. 
     *
     * @return true or false
     */
    public function MoveLast();

    /**
     * MoveNext: Fetch next row and check if we're at the end
     */
    public function MoveNext();

    /**
     * Random access to a specific row in the recordset. Some databases do not support
     * access to previous rows in the databases (no scrolling backwards).
     *
     * @param rowNumber is the row to move to (0-based)
     *
     * @return true if there still rows available, or false if there are no more rows (EOF).
     */
    public function Move($rowNumber = 0);

    /**
     * @return the current row in the recordset. If at EOF, will return the last row. 0-based.
     */
    public function CurrentRow();

    /**
     * @return the number of columns in the recordset. Some databases will set this to 0
     * if no records are returned, others will return the number of columns in the query.
     */
    public function FieldCount();

    /**
     * Get the FieldObject of a specific column.
     *
     * @param fieldoffset	is the column position to access(0-based).
     *
     * @return the FieldObject for that column, or false.
     */
    public function FetchField($fieldoffset = -1);

    /**
     * Get the FieldObjects of all columns in an array.
     */
    public function FieldTypesArray();

    /**
     * Return the fields array of the current row as an object for convenience.
     * The default case is lowercase field names.
     *
     * @return the object with the properties set to the fields of the current row
     */
    public function FetchObj();

    /**
     * Return the fields array of the current row as an object for convenience.
     * The default case is uppercase.
     * 
     * @param $isupper to set the object property names to uppercase
     *
     * @return the object with the properties set to the fields of the current row
     */
    public function FetchObject($isupper=true);

    /**
     * Return the fields array of the current row as an object for convenience.
     * The default is lower-case field names.
     * 
     * @return the object with the properties set to the fields of the current row,
     * 	or false if EOF
     */
    public function FetchNextObj();

    /**
     * Return the fields array of the current row as an object for convenience. 
     * The default is upper case field names.
     * 
     * @param $isupper to set the object property names to uppercase
     *
     * @return the object with the properties set to the fields of the current row,
     * 	or false if EOF
     */
    public function FetchNextObject($isupper=true);

    /**
     * Clean up recordset
     *
     * @return true or false
     */
    public function Close();
}

