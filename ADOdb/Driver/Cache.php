<?php

namespace ADOdb\Driver;

interface Cache 
{
    public function writecache($key, $contents, $debug, $secs2cache);
    public function &readcache($key, &$err, $secs2cache, $rsClass);
    public function flushcache($key, $debug=false)
    public function flushall();
}
