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
    protected $dso;
    protected $connection;

    protected $hostname;
    protected $username;
    protected $password;
    protected $database;

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

    public function close()
    {
        $this->dso = null;
        if ($this->connection) {
            $this->connection->close();
        }
        $this->connection = null;
    }

    /**
     * Connect: Establish connection to a database
     * @param host String [optional]
     * @param user String [optional]
     * @param pass String [optional]
     * @param database String [optional]
     */
    public function connect($hostname = null,
                            $username = null,
                            $password = null,
                            $database = null,
                            $options = array())
    {
        if ($connection) {
            return false;
        }

        if ($hostname) $this->dso->setHostname($hostname);
        if ($username) $this->dso->setUsername($username);
        if ($password) $this->dso->setPassword($password);
        if ($database) $this->dso->setDatabase($database);

        $this->connection = self::create($this->dso);

        foreach ((array) $options as $option => $value) {
            $this->setAttribute($option, $value);
        }
        return true;
    }

    protected setAttribute($name, $value)
    {
        if ($this->connection) {
            $this->connection->setAttribute($name, $value);
        }
        $this->attributes[$name] = $value;
    }

    protected getAttribute($name)
    {
        return $this->attributes[$name];
    }

    protected static function create($dso)
    {
        return new \ADOdb\DataObject\PDO\DataObject();
    }

    public function getOne($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        return $statement->fetchColumn(0);
    }

    public function cacheGetOne($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        return $statement->fetchColumn(0);
    }

    public function getCol($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        $col = array();
        while ($val = $statement->fetchColumn(0)) {
            $col[] = $val;
        }
        return $col;
    }

    public function cacheGetCol($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        $col = array();
        while ($val = $statement->fetchColumn(0)) {
            $col[] = $val;
        }
        return $col;
    }

    /*
     * @return Array of results
     */
    public function getAll($statement, $vars = null)
    {
        $statement = $this->query($statement, $vars);
        return $statement->fetchAll();
    }

    /**
     * CacheGetAll: Wrapper to emulate cached GetAll
     * @param timeout int count of seconds for cache expiry
     * @param sql String query to execute
     * @param vars Array of variables to bind [optional]
     * @return Array of results
     */
    public function cacheGetAll($timeout, $statement, $vars = null)
    {
        $statement = $this->cacheQuery($timeout, $statement, $vars);
        return $statement->fetchAll();
    }

    public function execute($statement, array $vars = null)
    {
        return new ResultSet($this->query($statement, $vars));
    }

    /**
     * CacheExecute: Wrapper to emulate cached Execute
     * @param timeout int count of seconds for cache expiry
     * @param sql String query to execute
     * @param vars Array of variables to bind [optional]
     * @return ADODB_PDO_ResultSet object
     */
    public function cacheExecute($timeout, $statement, $vars = null)
    {
        return new ResultSet($this->cacheQuery($timeout, $statement, $vars));
    }

    protected function query($statement, $vars = null)
    {
        return $this->connection->query($statement, $vars);
    }

    protected function cacheQuery($timeout, $statement, $vars = null)
    {
        if ($this->hasCache()) {
            try {
                $cache = $this->getCache();
                $queryKey = $cache->getQueryKey($sql, $vars);
                $statement = $cache->read($queryKey, $timeout));
            } catch (\Exception $e) {
                // To log debug info
            }
            if ($statement === null) {
                // Cache miss
                $statement = $this->connection->query($sql, $vars);
                $cache->write($queryKey, $statement, $timeout);
            }
            return $statement;
        } else {
            throw new ConnectionException('No cache engine found!');
        }
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
}
