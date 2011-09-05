<?php

require __DIR__ . '/../ADOdb/ADOdb.php';

$db = NewADOConnection('mysql');
$db->Connect('localhost', 'root', 'root');
$rs = $db->Execute("SELECT 'dummy text' result");

while (!$rs->EOF) {
    echo 'Text: '. $rs->fields['result'] . "\n"; 
    $rs->MoveNext();
}


