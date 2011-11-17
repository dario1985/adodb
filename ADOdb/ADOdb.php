<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

/**
* NewADOConnection: Thin wrapper to generate a new ADOdb\Connection object
* @param connector String denoting type of database
* @return ADODB_PDO object
*/
function NewADOConnection($dsn)
{
    $dso = new DataSource($dsn);
    $Connection = ADOdb\Connection::create($dso);
    return $Connection;
}

function ADODB_AutoLoader($sClass)
{
    $sLibPath = __DIR__ . DIRECTORY_SEPARATOR;
    $sClassFile = str_replace('\\', DIRECTORY_SEPARATOR, str_replace('ADOdb\\', '', $sClass)).'.php';
    $sClassPath = $sLibPath . $sClassFile;
    if (file_exists($sClassPath)) {
        require($sClassPath);
    }
}

spl_autoload_register('ADODB_AutoLoader');
