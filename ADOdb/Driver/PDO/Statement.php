<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

use ADOdb\FieldObject as ADODB_FieldObject;

class Statement extends \PDOStatement
                implements \ADOdb\Statement
{
    protected $createdTime;
    
    protected function __construct()
    {
        $this->createdTime = time();
    }
    
    public function createdTime()
    {
        return $this->createdTime();
    }
    
    public function canSeek()
    {
        return false;
    }
    
    public function close()
    {
        return $this->closeCursor();
    }
    
    public function getColumnMeta($column_number = 0)
    {
        $pdo_metas = $this->getColumnMeta($column_number);
        $field = new ADODB_FieldObject();
        $field->_setDataInfo(array(
            'name' => $pdo_metas['name'],
            'max_length' => $pdo_metas['len'],
            'type' => $pdo_metas['native_type'],
        ));
        return $field;
    }
}
