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
    const FETCH_NUM = Driver::FETCH_NUM;
    const FETCH_ASSOC = Driver::FETCH_ASSOC;
    const FETCH_BOTH = Driver::FETCH_BOTH;
    
    protected $timeCreated;
    
    protected function __construct()
    {
        $this->timeCreated = time();
    }
    
    public function timeCreated()
    {
        return $this->timeCreated;
    }
    
    public function canSeek()
    {
        return false;
    }
    
    public function close()
    {
        return $this->closeCursor();
    }
    
    public function inTransaction()
    {
        return parent::inTransaction();
    }
    
    public function getColumnMeta($column_number = 0)
    {
        $pdo_metas = parent::getColumnMeta($column_number);
        return new ADODB_FieldObject(
                array(
                    'name' => $pdo_metas['name'],
                    'max_length' => $pdo_metas['len'],
                    'type' => $pdo_metas['native_type']
                ));
    }
    
    public function dump()
    {
        $metas = array();
        for ($col = 0, $nCols = $this->columnCount(); $col < $nCols; $col++) {
            $pdo_metas = parent::getColumnMeta($col);
            $metas[] = array(
                'name' => $pdo_metas['name'],
                'max_length' => $pdo_metas['len'],
                'type' => $pdo_metas['native_type']
            );
        }
        return array(
            'RESULTSET' => $this->fetchAll(self::FETCH_NUM), 
            'COLUMN_META' => $metas, 
            'CREATED' => $this->timeCreated
        );
    }
}
