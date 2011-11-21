<?php

/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * Connection
 */
class Connection
{

    const FETCH_DEFAULT = 0;
    const FETCH_NUM = 1;
    const FETCH_ASSOC = 2;
    const FETCH_BOTH = 3;

    protected $dso;
    
    /**
     * @var Driver
     */
    protected $connection;
    protected $hostname;
    protected $username;
    protected $password;
    protected $database;
    protected $fetchMode;
    protected $attributes = array();

    public function __construct($dsn = '')
    {
        $dso = new DataSource($dsn);
        $this->hostname = $dso->getHostname();
        $this->username = $dso->getUsername();
        $this->password = $dso->getPassword();
        $this->database = $dso->getDatabase();
        $this->attributes = $dso->getOptions();
        $this->dso = $dso;
    }

    public function __destruct()
    {
        $this->close();
    }

    /**
     * Close connection 
     */
    public function close()
    {
        $this->dso = null;
        $this->connection = null;
    }

    /**
     * Connect: Establish connection to a database
     * @param string $hostname Hostname[:port] overriding datasource specs [optional]
     * @param string $username Username overriding datasource specs  [optional]
     * @param string $passname Password overriding datasource specs [optional]
     * @param string $database Database name overriding datasource specsString [optional]
     * @return boolean
     */
    public function connect($hostname = null, $username = null, $password = null, $database = null, $options = array())
    {
        if ($this->connection) {
            return false;
        }

        if ($hostname)
            $this->dso->setHostname($hostname);
        if ($username)
            $this->dso->setUsername($username);
        if ($password)
            $this->dso->setPassword($password);
        if ($database)
            $this->dso->setDatabase($database);

        $this->connection = Driver\DriverManager::create($this->dso);

        foreach ((array) $options as $option => $value) {
            $this->setAttribute($option, $value);
        }
        return true;
    }

    protected function setAttribute($name, $value)
    {
        if ($this->connection) {
            $this->connection->setAttribute($name, $value);
        }
        $this->attributes[$name] = $value;
    }

    protected function getAttribute($name)
    {
        return $this->attributes[$name];
    }

    public function setCache(Cache $cache)
    {
        $this->cache = $cache;
    }
    
    public function hasCache()
    {
        return ($this->cache !== null);
    }
    
    protected function getCache()
    {
        return $this->cache;
    }
    
    /**
     * Start new transaction
     * 
     * @return type 
     */
    public function startTrans() 
    {
        if (!$this->connection->inTransaction()) {
            return $this->connection->beginTransaction();
        } else return false;
    }
    
    /**
     * Complete transaction
     * 
     * @param type $success
     * @return boolean 
     */
    public function completeTrans($success = true)
    {
        if (!$this->connection->inTransaction()) {
            return false;
        }
        if ($success) {
            $this->connection->commit();
        } else {
            $this->connection->rollBack();
        }
    }
    
    /**
     * GetRow: return array of value of first row
     * 
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array 
     */
    public function getRow($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        return $statement->fetch(0);
    }

    /**
     * CacheGetRow: cached GetRow
     * 
     * @param int $timeout count of seconds for cache expiry
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array 
     */
    public function cacheGetRow($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        return $statement->fetch(0);
    }

    /**
     * GetOne: return first value of first row
     * 
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return mixed 
     */
    public function getOne($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        return $statement->fetchColumn(0);
    }

    /**
     * CacheGetOne: cached GetOne
     * 
     * @param int $timeout count of seconds for cache expiry
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return mixed 
     */
    public function cacheGetOne($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        return $statement->fetchColumn(0);
    }

    /**
     * GetCol: return array of value of first column
     * 
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array 
     */
    public function getCol($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        $col = array();
        while ($val = $statement->fetchColumn(0)) {
            $col[] = $val;
        }
        return $col;
    }

    /**
     * CacheGetCol: cached GetCol
     * @param int $timeout count of seconds for cache expiry
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array 
     */
    public function cacheGetCol($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        $col = array();
        while ($val = $statement->fetchColumn(0)) {
            $col[] = $val;
        }
        return $col;
    }

    /**
     * GetAll: return array of results
     * 
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array Array of results
     */
    public function getAll($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        return $statement->fetchAll();
    }

    /**
     * CacheGetAll: cached GetAll
     * 
     * @param int $timeout count of seconds for cache expiry
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return array Array of results
     */
    public function cacheGetAll($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        return $statement->fetchAll();
    }

    /**
     * CacheExecute
     * 
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return ResultSet|false object or false if fail
     */
    public function execute($statement, array $vars = null)
    {
        $st = $this->query($statement, $vars);
        if ($st !== false) {
            return new ResultSet($st);
        } else
            return false;
    }

    /**
     * CacheExecute: cached Execute
     * 
     * @param int $timeout count of seconds for cache expiry
     * @param string $statement String query to execute
     * @param array $vars Array of variables to bind [optional]
     * @return ResultSet|null object or false if fail
     */
    public function cacheExecute($timeout, $statement, $vars = null)
    {
        return new ResultSet($this->cacheQuery($timeout, $statement, $vars));
    }

    /**
     * Run a command that will talk to the connection
     *
     * @param Command $command
     * @return boolean
     */
    public function execCommand(Command $command)
    {
        return $command->execute($this);
    }

    /**
     * @param int $fetchMode 
     * @return type
     * @throws ConnectionException 
     */
    public function setFetchMode($fetchMode)
    {
        if (!$c = $this->connection)
            throw new ConnectionException('No connected!');

        switch ($fetchMode) {
            case self::FETCH_DEFAULT:
                return $c->setFetchMode($c::FETCH_DEFAULT);
            case self::FETCH_ASSOC:
                return $c->setFetchMode($c::FETCH_ASSOC);
            case self::FETCH_NUM:
                return $c->setFetchMode($c::FETCH_NUM);
            case self::FETCH_BOTH:
                return $c->setFetchMode($c::FETCH_BOTH);
            default:
                throw new ConnectionException('Invalid fetch mode value');
        }
    }

    /**
     * @param string $statement query statement
     * @param array $vars [optional]
     * @return Statement object 
     */
    protected function query($statement, $vars = null)
    {
        return $this->connection->query($statement, $vars);
    }

    /**
     * @param int $timeout
     * @param string $statement query statement
     * @param array $vars [optional]
     * @return Statement object
     * @throws ConnectionException 
     */
    protected function cacheQuery($timeout, $statement, $vars = null)
    {
        if ($this->hasCache()) {
            $st = null;
            try {
                $cache = $this->getCache();
                $queryKey = $cache->getQueryKey($statement, $vars);
                $st = $cache->read($queryKey, $timeout);
            } catch (\Exception $e) {
                // To log debug info
            }
            if (!$st) {
                // Cache miss
                $st = $this->connection->query($statement, $vars);
                $cache->write($queryKey, $st, $timeout);
            }
            return $st;
        } else {
            throw new ConnectionException('No cache engine found!');
        }
    }
}
