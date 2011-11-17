<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

use ADOdb\Driver\Cache as DriverCache;

abstract class Cache implements DriverCache
{
    const TYPE_FILE = 1;

    public function getQueryKey($sql, $params)
    {
        return '';
    }

    public static function create($type = self::TYPE_FILE)
    {
        switch ($type) {
            case self::TYPE_FILE:
            default:
                $cache = new Driver\Cache\File();
                return $cache;
	    }
    }
}
