
extern zend_class_entry *adodb_connection_ce;

ZEPHIR_INIT_CLASS(ADOdb_Connection);

PHP_METHOD(ADOdb_Connection, __construct);
PHP_METHOD(ADOdb_Connection, __destruct);
PHP_METHOD(ADOdb_Connection, __set);
PHP_METHOD(ADOdb_Connection, __get);
PHP_METHOD(ADOdb_Connection, connect);
PHP_METHOD(ADOdb_Connection, close);
PHP_METHOD(ADOdb_Connection, setDebug);
PHP_METHOD(ADOdb_Connection, setAttribute);
PHP_METHOD(ADOdb_Connection, getAttribute);
PHP_METHOD(ADOdb_Connection, setCache);
PHP_METHOD(ADOdb_Connection, startTrans);
PHP_METHOD(ADOdb_Connection, completeTrans);
PHP_METHOD(ADOdb_Connection, getRow);
PHP_METHOD(ADOdb_Connection, cacheGetRow);
PHP_METHOD(ADOdb_Connection, getOne);
PHP_METHOD(ADOdb_Connection, cacheGetOne);
PHP_METHOD(ADOdb_Connection, getCol);
PHP_METHOD(ADOdb_Connection, cacheGetCol);
PHP_METHOD(ADOdb_Connection, getAll);
PHP_METHOD(ADOdb_Connection, cacheGetAll);
PHP_METHOD(ADOdb_Connection, execute);
PHP_METHOD(ADOdb_Connection, cacheExecute);
PHP_METHOD(ADOdb_Connection, execCommand);
PHP_METHOD(ADOdb_Connection, setFetchMode);
PHP_METHOD(ADOdb_Connection, query);
PHP_METHOD(ADOdb_Connection, cacheQuery);
PHP_METHOD(ADOdb_Connection, debug);
PHP_METHOD(ADOdb_Connection, checkConnected);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection___construct, 0, 0, 0)
  ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection___set, 0, 0, 2)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection___get, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_connect, 0, 0, 0)
  ZEND_ARG_INFO(0, hostname)
  ZEND_ARG_INFO(0, username)
  ZEND_ARG_INFO(0, password)
  ZEND_ARG_INFO(0, database)
  ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_setdebug, 0, 0, 1)
  ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_setattribute, 0, 0, 2)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_getattribute, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_setcache, 0, 0, 1)
  ZEND_ARG_INFO(0, cache)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_completetrans, 0, 0, 0)
  ZEND_ARG_INFO(0, success)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_getrow, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cachegetrow, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_getone, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cachegetone, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_getcol, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cachegetcol, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_getall, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cachegetall, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cacheexecute, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_execcommand, 0, 0, 1)
  ZEND_ARG_INFO(0, command)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_setfetchmode, 0, 0, 1)
  ZEND_ARG_INFO(0, fetchMode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_query, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_cachequery, 0, 0, 2)
  ZEND_ARG_INFO(0, timeout)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_connection_debug, 0, 0, 0)
  ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_connection_method_entry) {
	PHP_ME(ADOdb_Connection, __construct, arginfo_adodb_connection___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_Connection, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(ADOdb_Connection, __set, arginfo_adodb_connection___set, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, __get, arginfo_adodb_connection___get, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, connect, arginfo_adodb_connection_connect, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, close, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, setDebug, arginfo_adodb_connection_setdebug, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, setAttribute, arginfo_adodb_connection_setattribute, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Connection, getAttribute, arginfo_adodb_connection_getattribute, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Connection, setCache, arginfo_adodb_connection_setcache, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, startTrans, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, completeTrans, arginfo_adodb_connection_completetrans, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, getRow, arginfo_adodb_connection_getrow, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, cacheGetRow, arginfo_adodb_connection_cachegetrow, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, getOne, arginfo_adodb_connection_getone, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, cacheGetOne, arginfo_adodb_connection_cachegetone, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, getCol, arginfo_adodb_connection_getcol, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, cacheGetCol, arginfo_adodb_connection_cachegetcol, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, getAll, arginfo_adodb_connection_getall, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, cacheGetAll, arginfo_adodb_connection_cachegetall, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, execute, arginfo_adodb_connection_execute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, cacheExecute, arginfo_adodb_connection_cacheexecute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, execCommand, arginfo_adodb_connection_execcommand, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, setFetchMode, arginfo_adodb_connection_setfetchmode, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Connection, query, arginfo_adodb_connection_query, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Connection, cacheQuery, arginfo_adodb_connection_cachequery, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Connection, debug, arginfo_adodb_connection_debug, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Connection, checkConnected, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
