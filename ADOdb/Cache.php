<?php

namespace ADOdb;

use ADOdb\Drivers\Cache as DriverCache;

abstract class Cache implements DriverCache
{
    abstract public function read($key, $ttl);
    abstract public function write($key, $value, $ttl);
    abstract public function flush($key);
    abstract public function flushAll();
}
