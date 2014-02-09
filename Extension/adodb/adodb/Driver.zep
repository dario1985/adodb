/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

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
    public function execute(statement);
    public function query(statement, vars = null);
    public function inTransaction();
    public function getLastInsertId(name = null);
    public function rollBack();
}