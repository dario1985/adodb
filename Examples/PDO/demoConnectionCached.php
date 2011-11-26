<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

require 'config.php';

$db = NewADOConnection('mysql');
$cache = ADOdb\Cache::create();
$cache->setCacheDir('/tmp/adodb/');
$db->setCache($cache);
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);

/* ResultSet access */
echo "--- ResultSet (deprecated ->fields[<name>] access):\n";

$t0 = microtime(true);
$rs = $db->cacheExecute(TTL_CACHE, "SELECT 'dummy text' result");
while (!$rs->EOF) {
    echo '$rs->fields["result"]: '. $rs->fields['result'] . "\n"; 
    $rs->MoveNext();
}
w(null, $t0);
$rs = null;

echo "--- ResultSet Traversable:\n";
$t0 = microtime(true); 
$rs = $db->cacheExecute(TTL_CACHE, "SELECT 'dummy test' result");
foreach ($rs as $c => $row)
    echo $c . ': '. print_r($row, true) . "\n";
w(null, $t0);

// Demo GetAll
echo "--- GetAll:\n";
$t0 = microtime(true);
w($db->cacheGetAll(TTL_CACHE, "SELECT 'dummy text' result"), $t0);

// Demo GetOne
echo "--- GetOne:\n";
$t0 = microtime(true);
w($db->cacheGetOne(TTL_CACHE, "SELECT 'dummy text' result"), $t0);

// Demo GetRow
echo "--- GetRow:\n";
$t0 = microtime(true);
w($db->cacheGetRow(TTL_CACHE, "SELECT 'dummy text' result"), $t0);

// Demo GetCol
echo "--- GetCol:\n";
$t0 = microtime(true);
w($db->cacheGetCol(TTL_CACHE, "SELECT 'dummy text' result"), $t0);

$mem = round(memory_get_peak_usage()/ 0x100000, 3);
echo "\n=== Max memory peak: {$mem}M\n";