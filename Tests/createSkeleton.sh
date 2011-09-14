cd ..

phpunit --skeleton-test ADOdb\\ResultsetIterator ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Exception ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Connection ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Command ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\ConnectionException ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\FieldObject ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\ResultSet ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\ADOdb ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Cache ADOdb/ADOdb.php
mkdir ./Tests/ADOdb/
find ADOdb/ -type f -name *Test.php -exec mv {} ./Tests/ADOdb/ \;

phpunit --skeleton-test ADOdb\\Driver\\Connection ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Driver\\ResultSet ADOdb/ADOdb.php
mkdir ./Tests/ADOdb/Driver
find ADOdb/ -type f -name *Test.php -exec mv {} ./Tests/ADOdb/Driver/ \;

phpunit --skeleton-test ADOdb\\Driver\\Cache ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Driver\\Cache\\File ADOdb/ADOdb.php
mkdir ./Tests/ADOdb/Driver/Cache
find ADOdb/ -type f -name *Test.php -exec mv {} ./Tests/ADOdb/Driver/Cache/ \;

phpunit --skeleton-test ADOdb\\Driver\\PDO\\Connection ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Driver\\PDO\\FieldObject ADOdb/ADOdb.php
phpunit --skeleton-test ADOdb\\Driver\\PDO\\ResultSet ADOdb/ADOdb.php
mkdir ./Tests/ADOdb/Driver/PDO
find ADOdb/ -type f -name *Test.php -exec mv {} ./Tests/ADOdb/Driver/PDO/ \;
