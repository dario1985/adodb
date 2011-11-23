<?php

require __DIR__ . '/../../ADOdb/ADOdb.php';

define('TEST_PDO_HOSTNAME', 'localhost');
define('TEST_PDO_USERNAME', 'root');
define('TEST_PDO_PASSWORD', '');
define('TEST_PDO_DATABASE', '');
define('TEST_PDO_DSN', 'mysql://root@localhost');
define('TTL_CACHE', 3600);


/**
 * print_r alias with memory usage and time
 * @param mixed $data
 * @param float $time 
 */
function w($data, $time = null) {
    if (is_string($data)) 
        $data = rtrim($data)."\n";
    
    print_r($data);
    
    if ($time !== null) {
        echo "> Time: " , round(microtime(true) - $time, 3), "\n";
    }
    echo "> Mem Usage: " , round(memory_get_usage() / 0x100000, 3), "M\n";
}