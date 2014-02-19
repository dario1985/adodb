<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

class Libredis extends \ADOdb\Cache implements \ADOdb\Driver\Cache
{
    protected $connection;
    protected $libredis;

    public function __construct()
    {
        if (!function_exists('libredis')) {
            throw new \ADOdb\Exception('ADOdb Cache: Libredis Extension not loaded');
        } else {
            $this->libredis = \Libredis();
        }
    }

    public function __destruct()
    {
        $this->connection = $this->libredis = null;
    }

    public function connect($hostspec = '127.0.0.1:6379')
    {
        $this->connection = $this->libredis->get_connection($hostspec);
    }

    public function read($key, $ttl)
    {
        $val = $this->connection->get($key, $ttl * 1000);
        if ($val) {
            $st = $this->unserializeStatement($val);
            if ($st instanceof \ADOdb\Statement) {
                if ((time() - $st->timeCreated()) > $ttl) {
                    $this->flush($key);
                    return false;
                } else {
                    return $st;
                }
            } else {
                throw new \ADOdb\Exception('ADOdb Cache RedisLib: Cache is corrupted');
            }
        } else {
            return false;
        }
    }

    public function write($key, \ADOdb\Statement $value, $ttl)
    {
        $batch = $this->libredis->create_batch();
        $batch->cmd('SET', $key, $this->serializeStatement($value));
        $batch->cmd('EXPIRE', $key, "$ttl");
        if (false === $batch->execute($this->connection)) {
            throw new \ADOdb\Exception('ADOdb Cache RedisLib: cannot set value.');
        }
    }

    public function flush($key)
    {
        $batch = $this->libredis->create_batch();
        $batch->cmd('DEL', $key);
        return $batch->execute($this->connection);
    }

    public function flushAll()
    {
        $batch = $this->libredis->create_batch();
        $batch->cmd('KEYS', self::KEY_PREFIX . '*');
        $keys = array();
        if ($batch->execute($this->connection)) {
            while ($batch->next_reply($type, $key, $len)) {
                $keys[] = $key;
            }
            $batch = $this->libredis->create_batch();
            $batch->write('DEL ' . implode(' ', $keys) . "\r\n");
            return $batch->execute($this->connection);
        }
    }
}
