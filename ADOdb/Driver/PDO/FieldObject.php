<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

use ADOdb\FieldObject as ADODB_FieldObject;

/**
* Table field information wrapper
*/
class FieldObject extends ADODB_FieldObject
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
