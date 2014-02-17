
extern zend_class_entry *adodb_driver_pdo_statement_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_PDO_Statement);

PHP_METHOD(ADOdb_Driver_PDO_Statement, __construct);
PHP_METHOD(ADOdb_Driver_PDO_Statement, timeCreated);
PHP_METHOD(ADOdb_Driver_PDO_Statement, canSeek);
PHP_METHOD(ADOdb_Driver_PDO_Statement, close);
PHP_METHOD(ADOdb_Driver_PDO_Statement, getColumnMeta);
PHP_METHOD(ADOdb_Driver_PDO_Statement, columnCount);
PHP_METHOD(ADOdb_Driver_PDO_Statement, dump);
PHP_METHOD(ADOdb_Driver_PDO_Statement, errorCode);
PHP_METHOD(ADOdb_Driver_PDO_Statement, errorInfo);
PHP_METHOD(ADOdb_Driver_PDO_Statement, rowCount);
PHP_METHOD(ADOdb_Driver_PDO_Statement, execute);
PHP_METHOD(ADOdb_Driver_PDO_Statement, fetch);
PHP_METHOD(ADOdb_Driver_PDO_Statement, fetchAll);
PHP_METHOD(ADOdb_Driver_PDO_Statement, fetchColumn);
PHP_METHOD(ADOdb_Driver_PDO_Statement, setFetchMode);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement___construct, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_getcolumnmeta, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_fetch, 0, 0, 0)
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_fetchall, 0, 0, 0)
  ZEND_ARG_INFO(0, fetch_style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_fetchcolumn, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_statement_setfetchmode, 0, 0, 1)
  ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_pdo_statement_method_entry) {
	PHP_ME(ADOdb_Driver_PDO_Statement, __construct, arginfo_adodb_driver_pdo_statement___construct, ZEND_ACC_PROTECTED|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_Driver_PDO_Statement, timeCreated, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, canSeek, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, close, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, getColumnMeta, arginfo_adodb_driver_pdo_statement_getcolumnmeta, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, columnCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, dump, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, errorCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, errorInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, rowCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, execute, arginfo_adodb_driver_pdo_statement_execute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, fetch, arginfo_adodb_driver_pdo_statement_fetch, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, fetchAll, arginfo_adodb_driver_pdo_statement_fetchall, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, fetchColumn, arginfo_adodb_driver_pdo_statement_fetchcolumn, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Statement, setFetchMode, arginfo_adodb_driver_pdo_statement_setfetchmode, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
