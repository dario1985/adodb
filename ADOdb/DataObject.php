<?php

namespace ADOdb;

/**
* Data Object Interface
*/
interface DataObject
{
    public function beginTransaction();
    public function commit();
    public function errorCode();
    public function errorInfo();
    public function execute($statement);
    public function query ($statement);
    public function inTransaction();
    public function getLastInsertId ($name = null);
    public function rollBack();
}
