ADOdb-PHP5.3
=============

This is an experimental full refactorized version of ADOdb library for PHP 5.3+. 
The idea came from the fact that ADOdb, a well known database abstraction library, 
is getting older and older and doesn't take advantage of PHP5.3+'s more advanced features. 

This project was born with the hope to provide a more up-to-date and stronger engine. 
So far it has proven to be faster than original engine and it provides a compatibility 
layer to allow developers that have been using ADOdb for years to switch 
their application over to this version progressively. 

Drivers
-------

Actually only support generic PDO* connections.


Caching
-------

Various engines supported out-of-box:

1. Memory (per-request) useful for testing purposes
2. APC
3. File
4. Libredis

Usage
-----

It's quite fully compatible with old ADOdb sintax:

    require 'ADOdb.php'
    $db = NewADOConnection('mysql');
    $db->connect($server, $user, $pwd, $db);