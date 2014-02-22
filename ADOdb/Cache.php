<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

use ADOdb\Driver\Cache as DriverCache;

class Cache
{
    const TYPE_MEMORY = 0;
    const TYPE_FILE = 1;
    const TYPE_APC = 2;
    const TYPE_LIBREDIS = 3;

    const KEY_PREFIX = 'DB_';

    public static function getQueryId($sql, array $params = null)
    {
        if ($params !== null) {
            return self::KEY_PREFIX . md5($sql . implode('', $params));
        } else {
            return self::KEY_PREFIX . md5($sql);
        }
    }

    public static function create($type = self::TYPE_MEMORY)
    {
        switch ($type) {
            case self::TYPE_MEMORY:
                return new Driver\Cache\Memory();
            case self::TYPE_APC:
                return new Driver\Cache\APC();
            case self::TYPE_LIBREDIS:
                return new Driver\Cache\Libredis();
            case self::TYPE_FILE:
            default:
                return new Driver\Cache\File();
        }
    }

    public static function serializeStatement(Statement $statement)
    {
        return gzcompress(serialize($statement->dump()), 3);
    }

    public static function unserializeStatement($serializedStatement)
    {
        $rawSt = unserialize(gzuncompress($serializedStatement));
        if ($rawSt !== false) {
            return new Driver\Cache\Statement($rawSt);
        } else {
            throw new Exception('Unserialize error');
        }
    }

    public static function createCacheableEstatement(Statement $statement)
    {
        return new Driver\Cache\Statement($statement->dump());
    }
}
