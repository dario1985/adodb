
extern zend_class_entry *adodb_resultset_ce;

ZEPHIR_INIT_CLASS(ADOdb_ResultSet);

PHP_METHOD(ADOdb_ResultSet, __construct);
PHP_METHOD(ADOdb_ResultSet, __destruct);
PHP_METHOD(ADOdb_ResultSet, __get);
PHP_METHOD(ADOdb_ResultSet, isEOF);
PHP_METHOD(ADOdb_ResultSet, recordCount);
PHP_METHOD(ADOdb_ResultSet, currentRow);
PHP_METHOD(ADOdb_ResultSet, getAssoc);
PHP_METHOD(ADOdb_ResultSet, fetchRow);
PHP_METHOD(ADOdb_ResultSet, nextRecordSet);
PHP_METHOD(ADOdb_ResultSet, moveFirst);
PHP_METHOD(ADOdb_ResultSet, moveLast);
PHP_METHOD(ADOdb_ResultSet, moveNext);
PHP_METHOD(ADOdb_ResultSet, move);
PHP_METHOD(ADOdb_ResultSet, fields);
PHP_METHOD(ADOdb_ResultSet, fieldTypesArray);
PHP_METHOD(ADOdb_ResultSet, fetchField);
PHP_METHOD(ADOdb_ResultSet, fieldCount);
PHP_METHOD(ADOdb_ResultSet, getIterator);
PHP_METHOD(ADOdb_ResultSet, count);
PHP_METHOD(ADOdb_ResultSet, close);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset___construct, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset___get, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset_getassoc, 0, 0, 0)
  ZEND_ARG_INFO(0, force_array)
  ZEND_ARG_INFO(0, first2cols)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset_move, 0, 0, 0)
  ZEND_ARG_INFO(0, rowNumber)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset_fields, 0, 0, 1)
  ZEND_ARG_INFO(0, colname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultset_fetchfield, 0, 0, 0)
  ZEND_ARG_INFO(0, column_number)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_resultset_method_entry) {
	PHP_ME(ADOdb_ResultSet, __construct, arginfo_adodb_resultset___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_ResultSet, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(ADOdb_ResultSet, __get, arginfo_adodb_resultset___get, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, isEOF, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, recordCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, currentRow, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, getAssoc, arginfo_adodb_resultset_getassoc, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, fetchRow, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, nextRecordSet, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, moveFirst, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, moveLast, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, moveNext, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, move, arginfo_adodb_resultset_move, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, fields, arginfo_adodb_resultset_fields, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, fieldTypesArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, fetchField, arginfo_adodb_resultset_fetchfield, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, fieldCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultSet, close, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
