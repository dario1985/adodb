<?php

namespace ADOdb\Driver\PDO;

use ADOdb\ResultSet as ADODB_Resultset;

/**
 * Resultset PDO
 */
class ResultSet extends ADODB_Resultset
{

    /**
     * PDOStatement object to wrap 
     * @var PDOStatement
     */
    protected $_st;

    /**
     * Constructor: Initialise resultset and first results
     * @param st PDOStatement object to wrap
     */
    public function __construct(\PDOStatement $st)
    {
        $this->_st = $st;
        $this->numOfRows = $this->_st->rowCount();
	$this->numOfFields = $this->_st->columnCount();
        $this->currentRow = -1;
        $this->MoveNext();
    }

    /**
     * Fetch a specific row in the recordset. 
     *
     * @param rowNumber is the row to move to (0-based)
     */
    protected function fetchRow($rowNumber = 0)
    {
        return $this->_st->fetch(
                \PDO::FETCH_ASSOC, \PDO::FETCH_ORI_ABS, $rowNumber
        );
    }

    /**
     * Clean up recordset
     *
     * @return true or false
     */
    public function Close()
    {
        return $this->_st->closeCursor();
    }

        /**
     * Get the FieldObject of a specific column.
     *
     * @param fieldoffset       is the column position to access(0-based).
     *
     * @return the FieldObject for that column, or false.
     */
    public function FetchField($fieldOffset = -1)
    {
         return new ADODB_PDO_FieldObject($this->_st->getColumnMeta($fieldOffset));
    }
}
