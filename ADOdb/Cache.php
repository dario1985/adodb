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
    const TYPE_FILE = 1;
    const TYPE_APC = 2;

    public static function getQueryId($sql, array $params = null)
    {
        if ($params !== null) {
            return md5($sql.implode('', $params));
        } else {
            return md5($sql);
        }
    }

    public static function create($type = self::TYPE_FILE)
    {
        switch ($type) {
            case self::TYPE_APC:
                return new Driver\Cache\APC();
            case self::TYPE_FILE:
            default:
                return new Driver\Cache\File();
        }
    }

    public static function serializeStatement(Statement $statement)
    {
        $RESULTSET = $statement->fetchAll($statement::FETCH_NUM);
        $COLUMN_META = array();
        for ($i = 0, $nCols = $statement->columnCount(); $i < $nCols; $i++) {
            $COLUMN_META[] = $statement->getColumnMeta($i);
        }
        $CREATED = $statement->createdTime();
        return serialize(compact('RESULTSET', 'COLUMN_META', 'CREATED'));
    }

    public static function unserializeStatement($serializedStatement)
    {
        $rawSt = unserialize($serializedStatement);
        if ($rawSt !== null) {
            return new Driver\Cache\Statement($rawSt);
        } else {
            throw new Exception('Unserialize error');
        }
    }
}
