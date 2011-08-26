<?php

namespace ADOdb\Driver\PDO;

use ADOdb\FieldData as ADODB_FieldData;

/**
* Table field information wrapper
*/
class FieldData extends ADODB_FieldData
{
    /**
    * Constructor: Map PDO meta information to object field data
    * @param meta Array from PDOStatement::getColumnMeta
    */
    public function __construct($meta)
    {
        $lut = array(
            'LONG' => 'int',
            'VAR_STRING' => 'varchar'
        );
        
        $this->name = $meta['name'];
        $this->max_length = $meta['len'];
        $this->type = $lut[$meta['native_type']];
    }
}
