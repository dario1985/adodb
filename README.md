ADOdb-PHP5.3 [![Build Status](https://travis-ci.org/dario1985/adodb.png)](https://travis-ci.org/dario1985/adodb) [![Coverage Status](https://coveralls.io/repos/dario1985/adodb/badge.png)](https://coveralls.io/r/dario1985/adodb) 
=============

This is an full refactored version of ADOdb library for PHP 5.3+.
The idea came from the fact that ADOdb, a well known database abstraction library, 
is getting older and older and doesn't take advantage of PHP5.3+'s more advanced features. 

This project was born with the hope to provide a more up-to-date and stronger engine. 
So far it has proven to be faster than original engine and it provides a compatibility 
layer to allow developers that have been using ADOdb for years to switch 
their application over to this version progressively.

This software is in development stage. Do not use it in production environments if you do not know what you are doing.


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

The syntax is similar (quite identical) to ADOdb sintax:

    require 'ADOdb.php';
    $db = NewADOConnection('mysql');
    $db->connect($server, $user, $pwd, $db);
    
License
-------

The MIT license, read it at http://www.opensource.org/licenses/mit-license.php

Contributing
------------

Feel free to fork and improve/enhance ADOdb in any way your want. 
If you feel that everybody will benefit from your changes, please open a pull request.
