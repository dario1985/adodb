
extern zend_class_entry *adodb_driver_cache_statement_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache_Statement);

PHP_METHOD(ADOdb_Driver_Cache_Statement, __construct);
PHP_METHOD(ADOdb_Driver_Cache_Statement, initResultsetData);
PHP_METHOD(ADOdb_Driver_Cache_Statement, __destruct);
PHP_METHOD(ADOdb_Driver_Cache_Statement, timeCreated);
PHP_METHOD(ADOdb_Driver_Cache_Statement, canSeek);
PHP_METHOD(ADOdb_Driver_Cache_Statement, close);
PHP_METHOD(ADOdb_Driver_Cache_Statement, errorCode);
PHP_METHOD(ADOdb_Driver_Cache_Statement, errorInfo);
PHP_METHOD(ADOdb_Driver_Cache_Statement, execute);
PHP_METHOD(ADOdb_Driver_Cache_Statement, columnCount);
PHP_METHOD(ADOdb_Driver_Cache_Statement, rowCount);
PHP_METHOD(ADOdb_Driver_Cache_Statement, fetch);
PHP_METHOD(ADOdb_Driver_Cache_Statement, fetchAll);
PHP_METHOD(ADOdb_Driver_Cache_Statement, fetchColumn);
PHP_METHOD(ADOdb_Driver_Cache_Statement, getColumnMeta);
PHP_METHOD(ADOdb_Driver_Cache_Statement, setFetchMode);
PHP_METHOD(ADOdb_Driver_Cache_Statement, dump);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement___construct, 0, 0, 0)
  ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_initresultsetdata, 0, 0, 1)
  ZEND_ARG_INFO(0, resultsetRawData)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_fetch, 0, 0, 0)
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_fetchall, 0, 0, 0)
  ZEND_ARG_INFO(0, fetch_style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_fetchcolumn, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_getcolumnmeta, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_statement_setfetchmode, 0, 0, 1)
  ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_cache_statement_method_entry) {
	PHP_ME(ADOdb_Driver_Cache_Statement, __construct, arginfo_adodb_driver_cache_statement___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_Driver_Cache_Statement, initResultsetData, arginfo_adodb_driver_cache_statement_initresultsetdata, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Driver_Cache_Statement, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(ADOdb_Driver_Cache_Statement, timeCreated, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, canSeek, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, close, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, errorCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, errorInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, execute, arginfo_adodb_driver_cache_statement_execute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, columnCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, rowCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, fetch, arginfo_adodb_driver_cache_statement_fetch, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, fetchAll, arginfo_adodb_driver_cache_statement_fetchall, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, fetchColumn, arginfo_adodb_driver_cache_statement_fetchcolumn, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, getColumnMeta, arginfo_adodb_driver_cache_statement_getcolumnmeta, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, setFetchMode, arginfo_adodb_driver_cache_statement_setfetchmode, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Statement, dump, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
