/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

class Memory extends \ADOdb\Cache implements \ADOdb\Driver\Cache
{
    protected _cache;

    public function __construct()
    {
        let this->_cache = [];
    }

    public function read(key, ttl)
    {
        if (isset(this->_cache[key])) {
            var st; let st = this->unserializeStatement(this->_cache[key]);
            if (st instanceof \ADOdb\Statement) {
                if ((time() - st->timeCreated()) > ttl) {
                    this->flush(key);
                    return false;
                } else {
                    return st;
                }
            } else {
                throw new \ADOdb\Exception("ADOdb Cache RedisLib: Cache is corrupted");
            }
        } else {
            return false;
        }
    }

    public function write(key, <\ADOdb\Statement> value, ttl)
    {
        let this->_cache[key] = this->serializeStatement(value);
    }

    public function flush(key)
    {
        unset(this->_cache[key]);
    }

    public function flushAll()
    {
        let this->_cache = [];
    }
}