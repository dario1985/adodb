<?php

/**
* NewADOConnection: Thin wrapper to generate a new ADOdb\Connection object
* @param connector String denoting type of database
* @return ADODB_PDO object
*/
function NewADOConnection($connector)
{
    return ADOdb\Connection::NewADOConnection($connector);
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
