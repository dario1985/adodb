<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

class ConnectionManager
{

    private $instance;

    public static function getInstance()
    {
        if (!self::$instance) {
            self::$instance = new ConnectionManager();
        }
        return self::$instance;
    }
}
