<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

use \PDO as PDO,
    \ADOdb\Driver as ADODB_Driver,
    \ADOdb\DataSource as ADODB_DataSource;

/**
 * Connection and query wrapper
 */
class Driver extends PDO 
                 implements ADODB_Driver
{
    const FETCH_DEFAULT = PDO::FETCH_ASSOC;

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
        $this->dsn = $this->connector
            . ':host=' . $this->hostname
            . ';dbname=' . $this->database;

        parent::__construct(
            $this->dsn,
            $this->username,
            $this->password
        );

        $this->setAttribute(PDO::ATTR_CURSOR, PDO::CURSOR_SCROLL);
        $this->setAttribute(
            PDO::ATTR_STATEMENT_CLASS,
            array('\ADOdb\Driver\PDO\Statement')
        );

        foreach ($this->pdoDriverOptions as $attr => &$value) {
            $this->setAttribute($attr, $value);
        }

        $this->setFetchMode(self::FETCH_DEFAULT);
    }

    public function setFetchMode($fetchMode)
    {
        parent::setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, $fetchMode);
        $this->fetchMode = $fetchMode;
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
    public function getLastInsertId($name = NULL)
    {
        return $this->lastInsertId($name);
    }

    public function query($statement, $vars = NULL)
    {
    if ($vars !== NULL) {
            $st = parent::prepare($statement);
            if ($st->execute($vars) !== false) {
                return $st;
            } else {
                return false;
            }
        } return parent::query($statement);
    }

    public function execute($sql, $vars=null)
    {
        return parent::exec($sql, $vars);
    }
}
