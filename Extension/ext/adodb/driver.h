
extern zend_class_entry *adodb_driver_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_query, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
  ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_getlastinsertid, 0, 0, 0)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_method_entry) {
	PHP_ABSTRACT_ME(ADOdb_Driver, beginTransaction, NULL)
	PHP_ABSTRACT_ME(ADOdb_Driver, commit, NULL)
	PHP_ABSTRACT_ME(ADOdb_Driver, errorCode, NULL)
	PHP_ABSTRACT_ME(ADOdb_Driver, errorInfo, NULL)
	PHP_ABSTRACT_ME(ADOdb_Driver, execute, arginfo_adodb_driver_execute)
	PHP_ABSTRACT_ME(ADOdb_Driver, query, arginfo_adodb_driver_query)
	PHP_ABSTRACT_ME(ADOdb_Driver, inTransaction, NULL)
	PHP_ABSTRACT_ME(ADOdb_Driver, getLastInsertId, arginfo_adodb_driver_getlastinsertid)
	PHP_ABSTRACT_ME(ADOdb_Driver, rollBack, NULL)
  PHP_FE_END
};
