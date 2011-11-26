<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

require 'config.php';

$db = NewADOConnection('mysql');
$db->Connect(TEST_PDO_HOSTNAME, TEST_PDO_USERNAME, TEST_PDO_PASSWORD);

const MAX_RECORDS = 1e6;

function create_table() {
    global $db;
    $db->execute('DROP TABLE IF EXISTS test.bench;');
    $db->execute('CREATE TABLE test.bench (
        id INT(11) AUTO_INCREMENT,
        intval INT(11),
        strval VARCHAR(50),
        PRIMARY KEY(id)
    ) ENGINE=InnoDB;');
}

function populate() {
    global $db;
    $insert_len = 100;
    $loop_len = (int) MAX_RECORDS / $insert_len;
    for($i = 0; $i < $loop_len; $i++) {
        $insert = 'INSERT INTO test.bench VALUES ';
        if (!$str || $t !== time()) {
            $t = time();
            $str = md5($t);
        }
        for($k = 0; $k < $insert_len; $k++) {
            $insert .= sprintf('(null, %d, "%s");',
                rand(1e3, 9e6), $str
            ); 
        }
        $db->execute($insert);
    }
}

create_table();
populate();