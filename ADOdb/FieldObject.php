<?php

/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * Table field information wrapper
 */
class FieldObject
{
    protected $name;
    protected $max_length;
    protected $type;
    protected $not_null = false;
    protected $has_default = false;
    protected $default_value; 
    
    public function __get($name) 
    {
        return $this->$name;
    }
    
    public function __set($name, $value = null)
    {
        $this->$name = $value;
    }
    
    public function _setDataInfo(array $fieldMetaData)
    {
        foreach ($fieldMetaData as $attr => $value) {
            $this->$attr = $value;
        }
    }
}
