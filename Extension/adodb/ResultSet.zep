/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * Resultset Class
 */
class ResultSet implements \Countable, \IteratorAggregate
{

    /**
     * Cache Driver
     * @var Cache
     */
    protected cache = null;

    /**
     * Statement object
     * @var Statement
     */
    protected statement = null;

    /* Publically Readonly accessible  __get() attributes: see publicProperties */
    protected p_fields = false;
    protected p_timeCreated;
    protected p_EOF = false;
    protected p_numOfRows = null;
    protected p_numOfFields = null;

    protected bufferedResults = null;
    protected canSeek;
    protected currentRow;
    protected publicProperties;

    public function __construct(statement)
    {
        let this->statement = statement;
        let this->p_timeCreated = statement->timeCreated();
        let this->canSeek = statement->canSeek();
        let this->p_numOfRows = statement->rowCount();
        let this->p_numOfFields = statement->columnCount();
        let this->currentRow = -1;

        let this->publicProperties = [
                    "timeCreated" : 1,
                    "numOfFields" : 1,
                    "numOfRows" : 1,
                    "fields" : 1,
                    "EOF" : 1
                ];
        this->moveNext();
    }

    public function __destruct()
    {
        this->close();
    }

    public function __get(name)
    {
        if (isset(this->publicProperties[name])) {
            let name = "p_" . name;
            return this->{name};
        }
    }

    public function isEOF() -> bool
    {
        return (bool) this->p_EOF;
    }

    /**
     * RecordCount: Retrieve number of records in this RS
     * @return Integer number of records
     */
    public function recordCount()
    {
        return this->p_numOfRows;
    }

    public function currentRow()
    {
        return this->currentRow;
    }

    /**
    * Return whole recordset as a 2-dimensional associative array if there are more than 2 columns.
    * The first column is treated as the key and is not included in the array.
    * If there is only 2 columns, it will return a 1 dimensional array of key-value pairs unless
    * force_array == true.
    *
    * @param bool force_array (Optional) has only meaning if we have 2 data columns. If false, a 1 dimensional
    * 	array is returned, otherwise a 2 dimensional array is returned. If this sounds confusing,
    * 	read the source.
    *
    * @param bool first2cols (Optional) means if there are more than 2 cols, ignore the remaining cols and
    * instead of returning array[col0] => array(remaining cols), return array[col0] => col1
    *
    * @return an associative array indexed by the first column of the array,
    * 	or false if the  data has less than 2 cols.
    */
    public function getAssoc(force_array = false, first2cols = false)
    {
        var cols; let cols = (int) this->p_numOfFields;
        if (cols < 2) {
            return false;
        }

        bool useNumIndex; let useNumIndex = isset(this->p_fields[0]);
        var results; let results = [];

        if (first2cols === false && (cols > 2 || force_array === true)) {
            if (useNumIndex === true) {
                while (!this->p_EOF) {
                    let results[trim(this->p_fields[0])] = array_slice(this->p_fields, 1, true);
                    this->moveNext();
                }
            } else {
                while (!this->p_EOF) {
                    let results[trim(reset(this->p_fields))] = array_slice(this->p_fields, 1, true);
                    this->moveNext();
                }
            }
        } else {
            if (useNumIndex === true) {
                while (!this->p_EOF) {
                    let results[trim(this->p_fields[0])] = this->p_fields[1];
                    this->moveNext();
                }
            } else {
                while (!this->p_EOF) {
                    var key, value;
                    let key = trim(reset(this->p_fields));
                    let value = next(this->p_fields);
                    let results[key] = value;
                    this->moveNext();
                }
            }
        }

        return results;
    }

    /**
    * Fetch a row, returning false if no more rows.
    * This is PEAR DB compat mode but widely used in ADOdb apps
    *
    * @return false or array containing the current record
    */
    public function fetchRow()
    {
        if (this->p_EOF) {
            return false;
        } else {
            var results; let results = this->p_fields;
            this->moveNext();
            return results;
        }
    }

    /**
     * Some databases allow multiple recordsets to be returned. This function
     * will return true if there is a next recordset, or false if no more.
     */
    public function nextRecordSet()
    {
        return this->statement->nextRowset();
    }

    /**
     * Move to the first row in the recordset.
     * Many databases do NOT support this.
     *
     * @return boolean
     */
    public function moveFirst()
    {
        if (this->currentRow === 0) {
            return true;
        }
        return this->move(0);
    }

    /**
     * Move to the last row in the recordset.
     *
     * @return boolean
     */
    public function moveLast()
    {
        if (this->p_numOfRows > 0) {
            return this->move(this->p_numOfRows - 2);
        }

        if (this->p_EOF) {
            return false;
        }
    }

    /**
     * MoveNext: Fetch next row and check if we"re at the end
     */
    public function moveNext()
    {
        if (!this->p_EOF && this->p_numOfRows >= this->currentRow) {
            let this->currentRow++;
            if (this->bufferedResults === null) {
                let this->p_fields = this->statement->$fetch();
            } else {
                let this->p_fields = this->bufferedResults[this->currentRow];
            }
            return true;
        } else {
            let this->p_fields = false;
            let this->p_EOF = true;
            return false;
        }
    }

    /**
     * Move: Random access to a specific row in the recordset.
     * Some databases do not support
     * access to previous rows in the databases (no scrolling backwards).
     *
     * @param rowNumber is the row to move to (0-based)
     *
     * @return true if there still rows available,
     *         or false if there are no more rows (EOF).
     */
    public function move(rowNumber = 0)
    {
        let this->p_EOF = false;

        if (this->p_numOfRows > 0 && rowNumber >= this->p_numOfRows) {
            let rowNumber = this->p_numOfRows - 2; // Overflow to last record
        }

        if (rowNumber == this->currentRow) {
            return true;
        }

        var fields;
        if (this->canSeek) {
            let fields = this->statement->$fetch(rowNumber);
        } else {
            if (this->bufferedResults === null) {
                let this->bufferedResults = this->statement->fetchAll();
            }
            let fields = this->bufferedResults[rowNumber];
        }

        if (fields) {
            let this->p_fields = fields;
            let this->currentRow = rowNumber;
            return true;
        }

        let this->p_fields = false;
        let this->p_EOF = true;
        return false;
    }

    /**
     * Get the value of a field in the current row by column name.
     * Will not work if ADODB_FETCH_MODE is set to ADODB_FETCH_NUM.
     *
     * @param colname  is the field to access
     *
     * @return the value of colname column
     */
    public function fields(colname)
    {
        return this->p_fields[colname];
    }

    /**
     * Get the FieldObjects of all columns in an array.
     *
     */
    public function fieldTypesArray()
    {
        var fields; let fields = [];
        int i = 0; var max; let max = this->fieldCount();
        for i in range(0, max - 1) {
            let fields[] = this->fetchField();
        }
        return fields;
    }

    public function fetchField(column_number = 0)
    {
        var field; let field = this->statement->getColumnMeta(column_number);
        if (field !== false) {
            return field;
        } else {
            throw new \Exception("Driver don\"t support Column Meta Data");
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
        return this->p_numOfFields;
    }

    //
    // IteratorAggregate Interface
    //

    /**
     * Return ResultSetIterator
     * @return RecordsetIterator
     */
    public function getIterator()
    {
        return new ResultsetIterator(this);
    }

    //
    // Countable Interface
    //

    /**
     * Return RecordCount
     * @return int Row Count
     */
    public function count()
    {
        return this->p_numOfRows;
    }

    public function close()
    {
        if (this->statement !== null) {
            return this->statement->close();
        }
    }
}