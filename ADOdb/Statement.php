<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

interface Statement
{
    public function errorCode();
    public function errorInfo();
    public function execute($parameters);
    public function columnCount();
    public function rowCount();
    public function canSeek();
    public function fetch($offset = null);
    public function fetchAll();
    public function fetchColumn($column_number = 0);
    public function getColumnMeta($column_number = 0);
    public function close();
}