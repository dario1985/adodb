<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

/**
 * DataSource string parser / maker
 *
 * @package    ADOdb
 * @author     Dario Mancuso <dario@ewide.eu>
 *
 * Variations accepted:
 *
 * type(dbsyntax)://username:password@protocol+hostspec/database?option=value
 * type://username:password@protocol+hostspec:110//usr/db_file.db
 * type://username:password@hostspec/database
 * type://username:password@hostspec
 * type://username@hostspec
 * type://hostspec/database
 * type://hostspec
 * type:///database
 * type:///database?option=value&anotheroption=anothervalue
 * type(dbsyntax)
 * type
 *
 * - type: Database backend used in PHP (i.e. mysql , odbc etc.)
 * - dbsyntax: Database used with regards to SQL syntax etc. When using ODBC as
 *   the type, set this to the DBMS type the ODBC driver is connecting to.
 *   Examples: access, db2, mssql, navision, solid, etc.
 *
 * - protocol: Communication protocol to use ( i.e. tcp, unix etc.)
 * - hostspec: Host specification (hostname[:port])
 * - database: Database to use on the DBMS server
 * - username: User name for login
 * - password: Password for login
 * - proto_opts: Maybe used with protocol
 * - option: Additional connection options in URI query string format. options
 *   get separated by &
 */
class DataSource
{
    const DSN_PARSE_REGEXP = '|^(?P<type>\w+)([\(](?P<dbsyntax>\w+)[\)])?(://(((?P<username>\w+)(:(?P<password>\w+))?)@)?(((?P<protocol>\w+)\+)?(?P<hostname>\w+)(:(?P<port>\d+))?)?(\/?(?P<database>[^\s\?]*)?)?(\?(?P<options>\S+))?)?$|i';

    protected $dsn;

    protected $type;
    protected $dbsyntax;
    protected $protocol;
    protected $hostname;
    protected $port;
    protected $database;
    protected $username;
    protected $password;
    protected $options;

    function __construct($dsn = NULL)
    {
        if ($dsn !== NULL) {
            $this->setDsn($dsn);
        }
    }

    public function __toString()
    {
        return $this->dsn;
    }

    public function getDsn()
    {
        return $this->dsn;
    }

    public function getType()
    {
        return $this->type;
    }

    public function getDbsyntax()
    {
        return $this->dbsyntax;
    }

    public function getProtocol()
    {
        return $this->protocol;
    }

    public function getHostname()
    {
        return $this->hostname;
    }

    public function getPort()
    {
        return $this->port;
    }

    public function getDatabase()
    {
        return $this->database;
    }

    public function getUsername()
    {
        return $this->username;
    }

    public function getPassword()
    {
        return $this->password;
    }

    public function getOptions()
    {
        return $this->options;
    }

    public function getOption($name)
    {
        if (isset($this->options[$name]))
            return $this->options[$name];
    }

    public function setDsn($value)
    {
        $this->dsn = $value;
        $parsed = @$this->parseDSN($this->dsn);
        foreach ($parsed as $name => $value) {
            $this->$name = $value;
        }
        return $this;
    }

    public function setType($value)
    {
        $this->type = $value;
        return $this;
    }

    public function setDbsyntax($value)
    {
        $this->dbsyntax = $value;
        return $this;
    }

    public function setProtocol($value)
    {
        $this->protocol = $value;
        return $this;
    }

    public function setHostname($value)
    {
        $this->hostname = $value;
        return $this;
    }

    public function setPort($value)
    {
        $this->port = (int) $value;
        return $this;
    }

    public function setDatabase($value)
    {
        $this->database = $value;
        return $this;
    }

    public function setUsername($value)
    {
        $this->username = $value;
        return $this;
    }

    public function setPassword($value)
    {
        $this->password = $value;
        return $this;
    }

    public function setOption($name, $value)
    {
        $this->options[$name] = $value;
    }

    protected function setOptions($value)
    {
        if (is_array($value)) {
            parse_str($value, $this->options);
        } else {
            $this->options = $value;
        }
        return $this;
    }

    /**
     * Parse a data source name
     *
     * @param $dsn string Data Source Name to be parsed
     *
     * @return array an associative array with the following keys:
     *
     *  type    : Database backend used in PHP (mysql, odbc etc.)
     *  dbsyntax: Database used with regards to SQL syntax etc.
     *  protocol: Communication protocol to use (tcp, unix etc.)
     *  hostname: Hostname specification
         *  port    : Port
     *  database: Database to use on the DBMS server
     *  username: User name for login
     *  password: Password for login
     *
     * The format of the supplied DSN is in its fullest form:
     *
     *  type(dbsyntax)://username:password@protocol+hostspec/database
     */
    protected static function parseDSN($dsn)
    {
        if (preg_match(self::DSN_PARSE_REGEXP, $dsn, $p)) {
            if ($options = $p['options']) {
                parse_str($options, $options);
            } else {
                $options = array();
            }
            return array(
                'type'     => $p['type'],
                'dbsyntax' => $p['dbsyntax'],
                'protocol' => $p['protocol'],
                'hostname' => $p['hostname'],
                'port'     => $p['port'],
                'database' => $p['database'],
                'username' => $p['username'],
                'password' => $p['password'],
                'options'  => $options
            );
        } else throw new \InvalidArgumentException('Invalid DSN: '. $dsn);
    }
}
