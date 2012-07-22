<?php
/*
 * Copyright 2012 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\OrientDB;

use \OrientDB as OrientDB,
    \ADOdb\Driver as ADODB_Driver,
    \ADOdb\DataSource as ADODB_DataSource;

/**
 * Connection and query wrapper
 */
class Driver extends OrientDB
             implements ADODB_Driver
{
    public function beginTransaction()
    {
        // TODO: Implement beginTransaction() method.
    }

    public function commit()
    {
        // TODO: Implement commit() method.
    }

    public function errorCode()
    {
        // TODO: Implement errorCode() method.
    }

    public function errorInfo()
    {
        // TODO: Implement errorInfo() method.
    }

    public function execute($statement)
    {
        // TODO: Implement execute() method.
    }

    public function query($statement, $vars = null)
    {
        // TODO: Implement query() method.
    }

    public function inTransaction()
    {
        // TODO: Implement inTransaction() method.
    }

    public function getLastInsertId($name = null)
    {
        // TODO: Implement getLastInsertId() method.
    }

    public function rollBack()
    {
        // TODO: Implement rollBack() method.
    }
}
