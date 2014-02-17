
extern zend_class_entry *adodb_command_ce;

ZEPHIR_INIT_CLASS(ADOdb_Command);

PHP_METHOD(ADOdb_Command, execute);
PHP_METHOD(ADOdb_Command, doQuery);
PHP_METHOD(ADOdb_Command, processResults);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_command_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, connection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_command_processresults, 0, 0, 1)
  ZEND_ARG_INFO(0, rs)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_command_method_entry) {
	PHP_ME(ADOdb_Command, execute, arginfo_adodb_command_execute, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Command, doQuery, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(ADOdb_Command, processResults, arginfo_adodb_command_processresults, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
