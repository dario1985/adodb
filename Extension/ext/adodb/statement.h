
extern zend_class_entry *adodb_statement_ce;

ZEPHIR_INIT_CLASS(ADOdb_Statement);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_execute, 0, 0, 1)
  ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_fetch, 0, 0, 0)
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_fetchall, 0, 0, 0)
  ZEND_ARG_INFO(0, fetch_style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_fetchcolumn, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_getcolumnmeta, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_statement_setfetchmode, 0, 0, 1)
  ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_statement_method_entry) {
	PHP_ABSTRACT_ME(ADOdb_Statement, errorCode, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, errorInfo, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, execute, arginfo_adodb_statement_execute)
	PHP_ABSTRACT_ME(ADOdb_Statement, columnCount, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, rowCount, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, canSeek, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, fetch, arginfo_adodb_statement_fetch)
	PHP_ABSTRACT_ME(ADOdb_Statement, fetchAll, arginfo_adodb_statement_fetchall)
	PHP_ABSTRACT_ME(ADOdb_Statement, fetchColumn, arginfo_adodb_statement_fetchcolumn)
	PHP_ABSTRACT_ME(ADOdb_Statement, getColumnMeta, arginfo_adodb_statement_getcolumnmeta)
	PHP_ABSTRACT_ME(ADOdb_Statement, close, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, timeCreated, NULL)
	PHP_ABSTRACT_ME(ADOdb_Statement, setFetchMode, arginfo_adodb_statement_setfetchmode)
	PHP_ABSTRACT_ME(ADOdb_Statement, dump, NULL)
  PHP_FE_END
};
