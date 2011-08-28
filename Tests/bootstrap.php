<?php

function ADODB_Test_AutoLoader($sClass)
{
    $sLibPath = __DIR__ . DIRECTORY_SEPARATOR . '..' .DIRECTORY_SEPARATOR;
    $sClassFile = str_replace('\\', DIRECTORY_SEPARATOR, $sClass) . '.php';
    $sClassPath = $sLibPath . $sClassFile;
    if (file_exists($sClassPath)) {
        require($sClassPath);
    }
}

spl_autoload_register('ADODB_Test_AutoLoader');
error_reporting(-1);
ini_set('display_errors', 1);