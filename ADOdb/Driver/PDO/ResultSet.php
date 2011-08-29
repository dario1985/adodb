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
    public function __construct(PDOStatement $st)
    {
        $this->_st = $st;
        $this->numOfRows = $this->_st->rowCount();
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
        $this->fields = $this->_st->fetch(
                PDO::FETCH_ASSOC, PDO::FETCH_ORI_ABS, $rowNumber
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

}
