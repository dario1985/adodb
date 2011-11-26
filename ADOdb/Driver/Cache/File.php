<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

class File extends \ADOdb\Cache implements \ADOdb\Driver\Cache
{
    protected $cache_dir = '/tmp/adodb/';
    protected $chmod = 0777;

    public function setCacheDir($path)
    {
        $path = realpath($path);
        if ($this->isValidPath($path)) {
            $this->cache_dir = $path . DIRECTORY_SEPARATOR;
        }
    }

    public function read($key, $ttl)
    {
        $file = $this->getCacheFile($key);
        if (file_exists($file)) {
            $st = $this->unserializeStatement(file_get_contents($file));
            if ($st instanceof \ADOdb\Statement) {
                if ((time() - $st->timeCreated()) > $ttl) {
                    $this->flush($key);
                    return false;
                } else {
                    return $st;
                }
            } else {
                throw new \ADOdb\Exception('ADOdb Cache File: Cache is corrupted');
            }
        } else return false;
    }

    public function write($key, \ADOdb\Statement $value, $ttl)
    {
        $dirname = $this->getDirName($key);
        if (!file_exists($dirname)) {
            mkdir($dirname, $this->chmod, true);
        }

        if ($this->isValidPath($dirname)) {
            $data = $this->serializeStatement($value);
            $file = $this->getCacheFile($key);
            if (file_put_contents($file, $data, LOCK_EX)) {
                chmod($file, $this->chmod);
            } else {
                throw new \ADOdb\Exception('ADOdb Cache File: Cannot write into file');
            }
        }
    }

    public function flush($key)
    {
        $file = $this->getCacheFile($key);

        if (file_exists($file) && !unlink($file)) {
            throw new \ADOdb\Exception('ADOdb Cache File: Cannot flush cache');
        }

        return true;
    }

    public function flushAll()
    {
        $it = new RecursiveIteratorIterator(
            new RecursiveDirectoryIterator($this->cache_dir),
            RecursiveIteratorIterator::CHILD_FIRST
        );

        foreach ($it as $file) {
            if (in_array($file->getBasename(), array('.', '..'))) {
                continue;
            } elseif ($file->isDir()) {
                rmdir($file->getPathname());
            } elseif ($file->isFile() || $file->isLink()) {
                unlink($file->getPathname());
            }
        }
    }

    protected function isValidPath($path)
    {
        if (!file_exists($path)) {
            throw new \ADOdb\Exception('ADOdb Cache File: No such file or directory');
        } elseif (!is_writable($path)) {
            throw new \ADOdb\Exception(sprintf('ADOdb Cache File: Cannot write in \'%s\'', $path));
        } else {
            return true;
        }
    }

    protected function getCacheFile($key)
    {
        return $this->getDirName($key) . $key . '.cache';
    }

    protected function getDirName($key)
    {
        return $this->cache_dir . substr($key, 0, 2) . DIRECTORY_SEPARATOR;
    }
}
