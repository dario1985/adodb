<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

class APC extends \ADOdb\Cache implements \ADOdb\Driver\Cache
{
    public function __construct()
    {
        if (!extension_loaded('apc')) {
            throw new \ADOdb\Exception('ADOdb Cache: APC Extension not loaded');
        }
        if (PHP_SAPI === 'cli') {
            user_error('APC Cache will don\'t persist between CLI executions.', E_USER_NOTICE);
        }
    }

    public function read($key, $ttl)
    {
        if ($val = apc_fetch($key)) {
            $st = $this->unserializeStatement($val);
            if ($st instanceof \ADOdb\Statement) {
                if ((time() - $st->timeCreated()) > $ttl) {
                    $this->flush($key);
                    return false;
                } else {
                    return $st;
                }
            } else {
                throw new \ADOdb\Exception('ADOdb Cache APC: Cache is corrupted');
            }
        } else {
            return false;
        }
    }

    public function write($key, \ADOdb\Statement $value, $ttl)
    {
        if (apc_store($key, $this->serializeStatement($value), $ttl) === false) {
            throw new \ADOdb\Exception('ADOdb Cache APC: Cannot store value. Is APC enabled?');
        } else {
            return true;
        }
    }

    public function flush($key)
    {
        return apc_delete($key);
    }

    public function flushAll()
    {
        return apc_clear_cache('user');
    }
}
