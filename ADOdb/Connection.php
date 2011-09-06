<?php

namespace ADOdb;

use ADOdb\Driver\Connection as DriverConnection,
    ADOdb\Driver\PDO\Connection as ADODB_PDO_Connection;

/**
* Connection and query wrapper
*/
abstract class Connection implements DriverConnection
{
    /**
    * NewADOConnection: Thin wrapper to generate a new ADODB_Connection object
    * @param connector String denoting type of database
    * @return ADODB_PDO object
    */
    static public function NewADOConnection($connector)
    {
        switch ($connector) {
            default:
            return new ADODB_PDO_Connection($connector);
        }
    }

    /**
     * Run a command that will talk to the connection
     *
     * @param Command $command
     * @return boolean
     */
    protected function execCommand(Command $command)
    {
        return $command->execute($this);
    }
}
