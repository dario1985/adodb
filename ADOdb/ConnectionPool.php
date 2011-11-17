<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

class ConnectionPool {

    private static $instance;

    protected $pool;
    protected $mode;

    const READ_WRITE = 1;
    const READ_ONLY = 2;

    public function __construct() {
        $this->pool= new \SplObjectStorage();
    }

    public function __destruct() {
        $this->pool = null;
    }

    /**
     * Add connection
     */
    public function add(Connection $connection) {
        $this->pool->attach($connection);
    }

    /**
     * Get connection
     */
    public function get() {
        if ($this->pool->count() > 0) {
            $this->pool->next();
            if (!$this->pool->valid()) {
                $this->rewind();
            }
            return $this->pool->current();
        } else {
            throw new Exception('Cannot found available connection!');
        }
    }
}