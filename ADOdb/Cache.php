<?php

namespace ADOdb;

use ADOdb\Driver\Cache as DriverCache;

abstract class Cache implements DriverCache
{
    const TYPE_FILE = 1;

    public static function createCache($type = self::TYPE_FILE)
    {
        switch ($type) {
            case self::TYPE_FILE:
            default:
                return new Driver\Cache\File();
	}
    }
}
