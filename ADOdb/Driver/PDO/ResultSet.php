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
        $this->rowcount = $this->_st->rowCount();
        $this->MoveNext();
    }

    public function &current()
    {
        return $this->fields;
    }

    public function next()
    {
        $this->fields = $this->_st->fetch();
    }

    public function key()
    {
        return $this->cursor;
    }

    public function valid()
    {
        return ($this->fields === false ? false : true);
    }

    public function rewind()
    {
        return true;
    }

    public function _close()
    {
        $this->_st->closeCursor();
    } 

    public function __destruct()
    {
        $this->_close();
    }
}
