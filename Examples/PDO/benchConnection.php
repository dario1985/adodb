<?php

require 'config.php';

$db = NewADOConnection('mysql');
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);
$sql = "SELECT SQL_NO_CACHE * FROM test.bench LIMIT 100000";

$ttotal0 = microtime(true);

goto RS_CLASSIC;

POPULATE:
for($i=0; $i<1e6; $i++) {
    $insert = sprintf('INSERT INTO test.bench VALUES (null, %d, "%s");',
        rand(1e3,9e6), md5(time())); 
    //echo $insert;
    $db->execute($insert);
}
die('POPULATED!');

RS_CLASSIC:
/* ResultSet access */
$t0 = microtime(true);
$rs = $db->Execute($sql);
while (!$rs->EOF) {
    $tmp = $rs->fields;
    $rs->MoveNext();
}
w('RS_CLASSIC', $t0);
$rs = null;
$tmp = null;

RS_ITERATOR:
$t0 = microtime(true);
$rs = $db->Execute($sql);
foreach ($rs as $c => $row){
    $tmp = $row;
}
w('RS_ITERATOR', $t0);
$rs = null;
$tmp = null;


GETALL:
// Demo GetAll
$t0 = microtime(true);
$db->getAll($sql);
w('GETALL', $t0);

GETONE:
// Demo GetOne
$t0 = microtime(true);
$db->getOne($sql);
w('GETONE', $t0);

GETROW:
// Demo GetRow
$t0 = microtime(true);
$db->getRow($sql);
w('GETROW', $t0);

GETCOL:
// Demo GetCol
$t0 = microtime(true);
$db->getCol($sql);
w('GETCOL', $t0);

END:
$t = round(microtime(true) - $ttotal0, 3);
echo "=== Time: {$t}s\n";
$mem = round(memory_get_peak_usage()/1024/1024,3);
echo "=== Max memory peak: {$mem}M\n";

