/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

/**
 * Connection and query wrapper
 */
class Driver implements \ADOdb\Driver
{
    const FETCH_DEFAULT = 2; // Same as \PDO::FETCH_ASSOC;

    /** Connection information (database name is public) */
    protected dsn;
    protected dso;
    protected hostname = "";
    protected username = "";
    protected password = "";
    protected database = "";

    protected connector = "";
    protected fetchMode;
    protected pdo;

    /** PDO demands fetchmodes on each resultset, so define a default */
    protected fetchmode;

    /** PDO drivers options:
     * This array holds one or more key=>value pairs to set attribute values
     * for the PDOStatement object that this method returns. You would most
     * commonly use this to set the PDO::ATTR_CURSOR value to PDO::CURSOR_SCROLL
     * to request a scrollable cursor. Some drivers have driver specific options
     * that may be set at prepare-time.
     */
    protected pdoDriverOptions;

    /**
     * Constructor: Initialise connector
     * @param connector String denoting type of database
     */
    public function __construct(dso)
    {
        let this->connector = dso->getType();
        let this->hostname = dso->getHostname();
        let this->username = dso->getUsername();
        let this->password = dso->getPassword();
        let this->database = dso->getDatabase();
        let this->pdoDriverOptions = dso->getOptions();

		if (this->connector === "sqlite" || this->connector === "sqlite2") {
			let this->dsn = this->connector . ":" . this->database;
		} else {
			let this->dsn = this->connector
                    . ":host=" . this->hostname
                    . ";dbname=" . this->database;
		}

        let this->pdo = new \PDO(
            this->dsn,
            this->username,
            this->password
        );

        this->setAttribute(\PDO::ATTR_CURSOR, \PDO::CURSOR_SCROLL);
		this->setAttribute(\PDO::ATTR_ERRMODE, \PDO::ERRMODE_EXCEPTION);

        var attr, value;
        for attr, value in this->pdoDriverOptions {
            this->setAttribute(attr, value);
        }

        this->setFetchMode(self::FETCH_DEFAULT);
    }

    public function setFetchMode(fetchMode)
    {
        switch (fetchMode) {
            case \ADOdb\Connection::FETCH_ASSOC:
                let fetchMode = \PDO::FETCH_ASSOC;
                break;
            case \ADOdb\Connection::FETCH_NUM:
                let fetchMode = \PDO::FETCH_NUM;
                break;
            case \ADOdb\Connection::FETCH_BOTH:
                let fetchMode = \PDO::FETCH_BOTH;
                break;
            default:
                throw new \ADOdb\ConnectionException("Unsupported fetch mode value");
        }
        this->pdo->setAttribute(\PDO::ATTR_DEFAULT_FETCH_MODE, fetchMode);
        let this->fetchMode = fetchMode;
    }

    public function setAttribute(attribute, value = null)
    {
        let this->pdoDriverOptions[attribute] = value;
        this->pdo->setAttribute(attribute, value);
    }

    public function getAttribute(attribute)
    {
        return this->pdoDriverOptions[attribute];
    }

    public function canScroll()
    {
        return (this->getAttribute(\PDO::ATTR_CURSOR) == \PDO::CURSOR_SCROLL);
    }

    /**
     * Retrieve the ID of the last insert operation
     * @return String containing last insert ID
     */
    public function getLastInsertId(name = null)
    {
        return this->pdo->lastInsertId(name);
    }

    public function inTransaction()
    {
        return this->pdo->inTransaction();
    }

    public function query(string statement, vars = null) -> < Statement > | bool
    {
        if (vars !== null) {
            var st; let st = this->pdo->prepare(statement);
            if (st !== false && st->execute(vars) !== false) {
                return new Statement(st);
            } else {
                return false;
            }
        }
        return this->pdo->query(statement);
    }

    public function execute(sql, vars=null)
    {
        return this->pdo->exec(sql, vars);
    }

    public function beginTransaction()
    {
        return this->pdo->beginTransaction();
    }

    public function commit()
    {
        return this->pdo->commit();
    }

    public function rollBack()
    {
        return this->pdo->rollBack();
    }

    public function errorCode()
    {
        return this->pdo->errorCode();
    }

    public function errorInfo()
    {
        return this->pdo->errorInfo();
    }
}