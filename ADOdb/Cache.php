<?php

namespace ADOdb;

use ADOdb\Drivers\Cache as DriverCache;

abstract class Cache implements DriverCache
{
    const TYPE_FILE = 1;

    public static function createCache($type = self::TYPE_FILE)
    {
        switch ($type) {
            case self::TYPE_FILE:
            default:
                return new Drivers\Cache\File();
    }

    abstract public function read($key, $ttl);
    abstract public function write($key, $value, $ttl);
    abstract public function flush($key);
    abstract public function flushAll();
}
