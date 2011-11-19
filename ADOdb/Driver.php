<?php

namespace ADOdb;

/**
* Data Object Interface
*/
interface Driver
{
    public function beginTransaction();
    public function commit();
    public function errorCode();
    public function errorInfo();
    public function execute($statement);
    public function query($statement, $vars = null);
    public function inTransaction();
    public function getLastInsertId($name = null);
    public function rollBack();
}
