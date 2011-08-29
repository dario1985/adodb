<?php

namespace ADOdb;

use ADOdb\Driver\FieldData as DriverFieldData;

/**
 * Table field information wrapper
 */
abstract class FieldData extends DriverFieldData
{

    public $name;
    public $max_length;
    public $type;

}
