<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

use \PDO as PDO;
use \ADOdb\Driver as ADODB_Driver;
use \ADOdb\DataSource as ADODB_DataSource;

/**
 * Connection and query wrapper
 */
class Driver extends PDO implements ADODB_Driver
{
    protected static $fetchStyles = array(
        \ADOdb\Connection::FETCH_NUM => self::FETCH_NUM,
        \ADOdb\Connection::FETCH_ASSOC => self::FETCH_ASSOC,
        \ADOdb\Connection::FETCH_BOTH => self::FETCH_BOTH
    );

    /** Connection information (database name is public) */
    protected $dsn;
    protected $dso;
    protected $hostname;
    protected $username;
    protected $password;
    protected $database;

    /** PDO demands fetchmodes on each resultset, so define a default */
    protected $fetchmode;

    /** PDO drivers options:
     * This array holds one or more key=>value pairs to set attribute values
     * for the PDOStatement object that this method returns. You would most
     * commonly use this to set the PDO::ATTR_CURSOR value to PDO::CURSOR_SCROLL
     * to request a scrollable cursor. Some drivers have driver specific options
     * that may be set at prepare-time.
     */
    protected $pdoDriverOptions = array();

    /**
     * Constructor: Initialise connector
     * @param connector String denoting type of database
     */
    public function __construct(ADODB_DataSource $dso)
    {
        $this->connector = $dso->getType();
        $this->hostname = $dso->getHostname();
        $this->username = $dso->getUsername();
        $this->password = $dso->getPassword();
        $this->database = $dso->getDatabase();
        $this->pdoDriverOptions = $dso->getOptions();

        if ($this->connector === 'sqlite' || $this->connector === 'sqlite2') {
            $this->dsn = $this->connector . ':' . $this->database;
        } else {
            $this->dsn = $this->connector
                . ':host=' . $this->hostname
                . ';dbname=' . $this->database;
        }

        parent::__construct(
            $this->dsn,
            $this->username,
            $this->password
        );

        $this->setAttribute(PDO::ATTR_CURSOR, PDO::CURSOR_SCROLL);
        $this->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $this->setAttribute(
            PDO::ATTR_STATEMENT_CLASS,
            array('\ADOdb\Driver\PDO\Statement')
        );

        foreach ($this->pdoDriverOptions as $attr => &$value) {
            $this->setAttribute($attr, $value);
        }

        $this->setFetchMode(self::FETCH_ASSOC);
    }

    public function setFetchMode($fetchMode)
    {
        if (isset(self::$fetchStyles[$fetchMode])) {
            $fetchMode = self::$fetchStyles[$fetchMode];
            parent::setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, $fetchMode);
            $this->fetchMode = $fetchMode;
        } else {
            throw new \ADOdb\ConnectionException('Unsupported fetch mode value');
        }
    }

    public function setAttribute($attribute, $value = null)
    {
        $this->pdoDriverOptions[$attribute] = $value;
        parent::setAttribute($attribute, $value);
    }

    public function getAttribute($attribute)
    {
        return $this->pdoDriverOptions[$attribute];
    }

    public function canScroll()
    {
        return ($this->getAttribute(PDO::ATTR_CURSOR) == PDO::CURSOR_SCROLL);
    }

    /**
     * Retrieve the ID of the last insert operation
     * @return String containing last insert ID
     */
    public function getLastInsertId($name = null)
    {
        return $this->lastInsertId($name);
    }

    public function inTransaction()
    {
        return parent::inTransaction();
    }

    public function query($statement, $vars = null)
    {
        if ($vars !== null) {
            $st = parent::prepare($statement);
            if ($st->execute($vars) !== false) {
                return $st;
            } else {
                return false;
            }
        }
        return parent::query($statement);
    }

    public function execute($sql, $vars = null)
    {
        return parent::exec($sql, $vars);
    }
}
