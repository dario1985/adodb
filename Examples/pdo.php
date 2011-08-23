<?php

require __DIR__ . '/../ADOdb/ADOdb.php';

$db = NewADOConnection('mysql');
$db->Connect('localhost', 'root', 'root');
$rs = $db->Execute('SELECT 1');

while (!$rs->EOF) {
    var_dump($rs->fields);
    $rs->MoveNext();
}


