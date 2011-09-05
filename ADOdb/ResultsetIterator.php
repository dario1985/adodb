<?php

namespace ADOdb;

/**
 * ResultsetIterator
 */
class ResultsetIterator implements \Iterator
{
    protected $rs;

    public function __construct(RecordSet $rs)
    {
        $this->rs = $rs;
    }

    public function rewind()
    {
        $this->rs->MoveFirst();
    }

    public function valid()
    {
        return !$this->rs->EOF;
    }

    public function key()
    {
        return $this->rs->CurrentRow();
    }

    public function current()
    {
        return $this->rs->fields;
    }

    public function next()
    {
        $this->rs->MoveNext();
    }

    public function __call($func, $params)
    {
        return call_user_func_array(array($this->rs, $func), $params);
    }

    public function hasMore()
    {
        return!$this->rs->EOF;
    }
}
