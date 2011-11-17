<?php

require __DIR__ . '/../../ADOdb/ADOdb.php';
require 'config.php';

$db = NewADOConnection('mysql');
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);

/* ResultSet */
echo "\n--- ResultSet:\n";

$rs = $db->Execute("SELECT 'dummy text' result");
while (!$rs->EOF) {
    echo 'Text: '. $rs->fields['result'] . "\n"; 
    $rs->MoveNext();
}
$rs = null;

// Demo GetAll
echo "\n--- GetAll:\n";
print_r($db->getAll("SELECT 'dummy text' result"));

// Demo GetOne
echo "\n--- GetOne:\n";
print_r($db->getOne("SELECT 'dummy text' result"));


// Demo GetCol
echo "\n\n--- GetCol:\n";
print_r($db->getCol("SELECT 'dummy text' result"));

