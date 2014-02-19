<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver;

interface Cache
{
    public function read($key, $ttl);

    public function write($key, \ADOdb\Statement $value, $ttl);

    public function flush($key);

    public function flushAll();
}
