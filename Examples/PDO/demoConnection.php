<?php

require __DIR__ . '/../../ADOdb/ADOdb.php';
require 'config.php';

$db = NewADOConnection('mysql');
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);

/* ResultSet access */
echo "\n--- ResultSet (deprecated ->fields[<name>] access):\n";

$rs = $db->Execute("SELECT 'dummy text' result");
while (!$rs->EOF) {
    echo '$rs->fields["result"]: '. $rs->fields['result'] . "\n"; 
    $rs->MoveNext();
}
$rs = null;

echo "\n--- ResultSet Traversable:\n";
$rs = $db->Execute("SELECT 'dummy test' result");
foreach ($rs as $c => $row)
    echo $c . ': '. print_r($row, true) . "\n";


// Demo GetAll
echo "\n--- GetAll:\n";
print_r($db->getAll("SELECT 'dummy text' result"));

// Demo GetOne
echo "\n--- GetOne:\n";
print_r($db->getOne("SELECT 'dummy text' result"));

// Demo GetRow
echo "\n--- GetRow:\n";
print_r($db->getRow("SELECT 'dummy text' result"));

// Demo GetCol
echo "\n\n--- GetCol:\n";
print_r($db->getCol("SELECT 'dummy text' result"));

$mem = round(memory_get_peak_usage()/1024/1024,3);
echo "\n\n=== Max memory peak: {$mem}M\n";