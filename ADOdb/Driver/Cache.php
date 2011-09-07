<?php

namespace ADOdb\Driver;

interface Cache 
{
    public function read($key, $ttl);
    public function write($key, \ADOdb\RecordSet $value, $ttl);
    public function flush($key);
    public function flushAll();

}
