<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * ResultsetIterator
 * 
 * Implementing 
 */
class ResultsetIterator implements \SeekableIterator
{
    /**
     * ResultSet Object
     * @var ResultSet
     */
    protected $rs;

    public function __construct(ResultSet $rs)
    {
        $this->rs = $rs;
    }

    public function seek($position)
    {
        $this->rs->move($position);
    }
    
    public function current()
    {
        return $this->rs->fields;
    }

    public function key()
    {
        return $this->rs->currentRow;
    }

    public function next()
    {
        $this->rs->moveNext();
    }


    public function rewind()
    {
        $this->rs->MoveFirst();
    }

    public function valid()
    {
        return !$this->rs->EOF;
    }
    
    public function __call($func, $params)
    {
        return call_user_func_array(array($this->rs, $func), $params);
    }
}
