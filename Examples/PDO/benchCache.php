<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

require 'config.php';

use ADOdb\Cache as ADODB_Cache;

/* Parsing CLI options */
$cli_options = getopt('', array('cache::'));
switch ($cli_options['cache']) {
    case 'memory':
        echo "=== Using MEMORY as cache ===\n";
        $cache = ADODB_Cache::create(ADODB_Cache::TYPE_MEMORY);
        break;
    case 'apc':
        echo "=== Using APC as cache ===\n";
        $cache = ADODB_Cache::create(ADODB_Cache::TYPE_APC);
        break;
    case 'libredis':
        echo "=== Using LIBREDIS as cache ===\n";
        $cache = ADODB_Cache::create(ADODB_Cache::TYPE_LIBREDIS);
        $cache->connect('localhost');
        break;
    case 'file':
    default:
        echo "=== Using FILE as cache ===\n";
        $cache = ADODB_Cache::create(ADODB_Cache::TYPE_FILE);
}

$db = NewADOConnection('mysql');
$db->setCache($cache);
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);

$sql = "SELECT SQL_NO_CACHE * FROM test.bench LIMIT 100000";

$ttotal0 = microtime(true);

goto RS_CLASSIC;

RS_CLASSIC:
/* ResultSet access */
$t0 = microtime(true);
$rs = $db->cacheExecute(TTL_CACHE, $sql);
while (!$rs->EOF) {
    $tmp = $rs->fields;
    $rs->MoveNext();
}
w('RS_CLASSIC', $t0);
$rs = $tmp = null;

RS_ITERATOR:
$t0 = microtime(true);
$rs = $db->cacheExecute(TTL_CACHE, $sql);
foreach ($rs as $c => $row){
    $tmp = $row;
}
w('RS_ITERATOR', $t0);
$rs = $tmp = null;


GETALL:
// Demo GetAll
$t0 = microtime(true);
$db->cacheGetAll(TTL_CACHE, $sql);
w('GETALL', $t0);

GETONE:
// Demo GetOne
$t0 = microtime(true);
$db->cacheGetOne(TTL_CACHE, $sql);
w('GETONE', $t0);

GETROW:
// Demo GetRow
$t0 = microtime(true);
$db->cacheGetRow(TTL_CACHE, $sql);
w('GETROW', $t0);

GETCOL:
// Demo GetCol
$t0 = microtime(true);
$db->cacheGetCol(TTL_CACHE, $sql);
w('GETCOL', $t0);

END:
$t = round(microtime(true) - $ttotal0, 3);
echo "=== Time: {$t}s\n";
$mem = round(memory_get_peak_usage()/1024/1024,3);
echo "=== Max memory peak: {$mem}M\n";

$cache->flushAll();
echo "=== Cache flushed!\n";

