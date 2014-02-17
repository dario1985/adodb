/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

class Connection
{

    const FETCH_DEFAULT = 0;
    const FETCH_NUM = 1;
    const FETCH_ASSOC = 2;
    const FETCH_BOTH = 3;

    protected dso;

    /**
     * @var Driver
     */
    protected connection;
    protected debug = false;
	protected cache;

    public function __construct(string dsn = "")
    {
        let this->dso = new DataSource(dsn);
    }

    public function __destruct()
    {
        this->close();
    }

    public function __set(string name, value)
    {
        // Deprecated old ADOdb access
        switch(name) {
            case "host" : this->dso->setHostname(value);
                break;
            case "database" : this->dso->setDatabase(value);
                break;
            case "user" : this->dso->setUsername(value);
                break;
            case "password" : this->dso->setPassword(value);
                break;
            case "debug" : this->setDebug(value);
                break;
        }
    }

    public function __get(string name)
    {
        // Deprecated old ADOdb access
        switch(name) {
            case "host" : return this->dso->getHostname();
            case "database" : return this->dso->getDatabase();
            case "user" : return this->dso->getUsername();
            case "password" : return this->dso->getPassword();
            case "debug" : return this->debug;
        }
    }

    /**
     * Connect: Establish connection to a database
     * @param string hostname Hostname[:port] overriding datasource specs [optional]
     * @param string username Username overriding datasource specs  [optional]
     * @param string passname Password overriding datasource specs [optional]
     * @param string database Database name overriding datasource specsString [optional]
     * @return boolean
     */
    public function connect(string hostname = null, string username = null, string password = null, string database = null, options = [])
    {
        if (this->connection) {
            return false;
        }

        if (hostname) {
            this->dso->setHostname(hostname);
        }
        if (username) {
            this->dso->setUsername(username);
		}
        if (password) {
            this->dso->setPassword(password);
		}
        if (database) {
            this->dso->setDatabase(database);
		}

        let this->connection = Driver\DriverManager::create(this->dso);

		var option, value;
        for option, value in options {
            this->setAttribute(option, value);
        }
        return true;
    }

    /**
     * Close connection
     */
    public function close()
    {
        let this->connection = null;
    }

    public function setDebug(flag)
    {
        let this->debug = (bool) flag;
    }

    protected function setAttribute(string name, value)
    {
        if (this->connection) {
            this->connection->setAttribute(name, value);
        }
        this->dso->setOption(name, value);
    }

    protected function getAttribute(string name)
    {
        return this->dso->getOption(name);
    }

    public function setCache(<ADOdb\Cache> cache)
    {
        let this->cache = cache;
    }

    /**
     * Start new transaction
     *
     * @return type
     */
    public function startTrans()
    {
        if (!this->connection->inTransaction()) {
            return this->connection->beginTransaction();
        } else {
        	return false;
        }
    }

    /**
     * Complete transaction
     *
     * @param type success
     * @return boolean
     */
    public function completeTrans(bool success = true)
    {
        if (!this->connection->inTransaction()) {
            return false;
        }
        if (success) {
            this->connection->commit();
        } else {
            this->connection->rollBack();
        }
    }

    /**
     * GetRow: return array of value of first row
     *
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array
     */
    public function getRow(statement, array vars = null)
    {
        var st; let st = this->query(statement, vars);
        return st->$fetch(0);
    }

    /**
     * CacheGetRow: cached GetRow
     *
     * @param int timeout count of seconds for cache expiry
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array
     */
    public function cacheGetRow(int timeout, string statement, array vars = null)
    {
        var st; let st = this->cacheQuery(timeout, statement, vars);
        return st->$fetch(0);
    }

    /**
     * GetOne: return first value of first row
     *
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return mixed
     */
    public function getOne(string statement, array vars = null)
    {
        var st; let st = this->query(statement, vars);
        return st->fetchColumn(0);
    }

    /**
     * CacheGetOne: cached GetOne
     *
     * @param int timeout count of seconds for cache expiry
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return mixed
     */
    public function cacheGetOne(int timeout, string statement, array vars = null)
    {
        var st; let st = this->cacheQuery(timeout, statement, vars);
        return st->fetchColumn(0);
    }

    /**
     * GetCol: return array of value of first column
     *
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array
     */
    public function getCol(string statement, array vars = null)
    {
        var col, val;
        var st; let st = this->query(statement, vars);
        let col = [];
        let val = st->fetchColumn(0);
        while val {
            let col[] = val;
            let val = st->fetchColumn(0);
        }
        return col;
    }

    /**
     * CacheGetCol: cached GetCol
     * @param int timeout count of seconds for cache expiry
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array
     */
    public function cacheGetCol(int timeout, string statement, array vars = null)
    {
        var col, val;
        var st; let st = this->cacheQuery(timeout, statement, vars);
        let col = [];
        let val = st->fetchColumn(0);
        while val {
            let col[] = val;
            let val = st->fetchColumn(0);
        }
        return col;
    }

    /**
     * GetAll: return array of results
     *
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array Array of results
     */
    public function getAll(string statement, array vars = null)
    {
        var st; let st = this->query(statement, vars);
        return st->fetchAll();
    }

    /**
     * CacheGetAll: cached GetAll
     *
     * @param int timeout count of seconds for cache expiry
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return array Array of results
     */
    public function cacheGetAll(int timeout, string statement, array vars = null)
    {
        var st; let st = this->cacheQuery(timeout, statement, vars);
        return st->fetchAll();
    }

    /**
     * CacheExecute
     *
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return ResultSet|false object or false if fail
     */
    public function execute(string statement, array vars = null)
    {
        var st;
        let st = this->query(statement, vars);
        if (st !== false) {
            return new ResultSet(st);
        } else {
            return false;
		}
    }

    /**
     * CacheExecute: cached Execute
     *
     * @param int timeout count of seconds for cache expiry
     * @param string statement String query to execute
     * @param array vars Array of variables to bind [optional]
     * @return ResultSet|null object or false if fail
     */
    public function cacheExecute(int timeout, string statement, array vars = null)
    {
        return new ResultSet(this->cacheQuery(timeout, statement, vars));
    }

    /**
     * Run a command that will talk to the connection
     *
     * @param Command command
     * @return boolean
     */
    public function execCommand(<Command> command)
    {
		return command->execute(this);
    }

    /**
     * @param int fetchMode
     * @return type
     * @throws ConnectionException
     */
    public function setFetchMode(fetchMode)
    {
        this->checkConnected();

        switch (fetchMode) {
            case self::FETCH_DEFAULT:
            case self::FETCH_ASSOC:
            case self::FETCH_NUM:
            case self::FETCH_BOTH:
                return this->connection->setFetchMode(fetchMode);
            default:
                throw new ConnectionException("Invalid fetch mode value");
        }
    }

    /**
     * @param string statement query statement
     * @param array vars [optional]
     * @return Statement object
     */
    protected function query(string statement, array vars = null)
    {
        this->checkConnected();
        return this->connection->query(statement, vars);
    }

    /**
     * @param int timeout
     * @param string statement query statement
     * @param array vars [optional]
     * @return Statement object
     * @throws ConnectionException
     */
    protected function cacheQuery(int timeout, string statement, array vars = null)
    {
        if (this->cache !== null) {
        	var queryId, st;
            let queryId = this->cache->getQueryId(statement, vars);
            let st = this->cache->read(queryId, timeout);
            if (!st) {
                // Cache miss
                this->debug("Cache miss!");
                let st = this->connection->query(statement, vars);
                this->cache->write(queryId, st, timeout);
            }
            return st;
        } else {
            user_error("No cache engine found!", E_USER_WARNING);
            return $this->query($statement, $vars);
        }
    }

    protected function debug(string msg = "")
    {
        if (this->debug === true) {
            printf("% 10d: %s\n", memory_get_usage(), msg);
        }
    }

    protected function checkConnected()
    {
        if (!this->connection) {
            throw new ConnectionException("No connected!");
        }
    }
}