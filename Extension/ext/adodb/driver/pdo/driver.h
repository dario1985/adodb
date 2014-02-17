
extern zend_class_entry *adodb_driver_pdo_driver_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_PDO_Driver);

PHP_METHOD(ADOdb_Driver_PDO_Driver, __construct);
PHP_METHOD(ADOdb_Driver_PDO_Driver, setFetchMode);
PHP_METHOD(ADOdb_Driver_PDO_Driver, setAttribute);
PHP_METHOD(ADOdb_Driver_PDO_Driver, getAttribute);
PHP_METHOD(ADOdb_Driver_PDO_Driver, canScroll);
PHP_METHOD(ADOdb_Driver_PDO_Driver, getLastInsertId);
PHP_METHOD(ADOdb_Driver_PDO_Driver, inTransaction);
PHP_METHOD(ADOdb_Driver_PDO_Driver, query);
PHP_METHOD(ADOdb_Driver_PDO_Driver, execute);
PHP_METHOD(ADOdb_Driver_PDO_Driver, beginTransaction);
PHP_METHOD(ADOdb_Driver_PDO_Driver, commit);
PHP_METHOD(ADOdb_Driver_PDO_Driver, rollBack);
PHP_METHOD(ADOdb_Driver_PDO_Driver, errorCode);
PHP_METHOD(ADOdb_Driver_PDO_Driver, errorInfo);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver___construct, 0, 0, 1)
  ZEND_ARG_INFO(0, dso)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_setfetchmode, 0, 0, 1)
  ZEND_ARG_INFO(0, fetchMode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_setattribute, 0, 0, 1)
  ZEND_ARG_INFO(0, attribute)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_getattribute, 0, 0, 1)
  ZEND_ARG_INFO(0, attribute)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_getlastinsertid, 0, 0, 0)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_query, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_pdo_driver_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, sql)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_pdo_driver_method_entry) {
	PHP_ME(ADOdb_Driver_PDO_Driver, __construct, arginfo_adodb_driver_pdo_driver___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_Driver_PDO_Driver, setFetchMode, arginfo_adodb_driver_pdo_driver_setfetchmode, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, setAttribute, arginfo_adodb_driver_pdo_driver_setattribute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, getAttribute, arginfo_adodb_driver_pdo_driver_getattribute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, canScroll, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, getLastInsertId, arginfo_adodb_driver_pdo_driver_getlastinsertid, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, inTransaction, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, query, arginfo_adodb_driver_pdo_driver_query, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, execute, arginfo_adodb_driver_pdo_driver_execute, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, beginTransaction, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, commit, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, rollBack, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, errorCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_PDO_Driver, errorInfo, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
