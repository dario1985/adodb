
extern zend_class_entry *adodb_resultsetiterator_ce;

ZEPHIR_INIT_CLASS(ADOdb_ResultsetIterator);

PHP_METHOD(ADOdb_ResultsetIterator, __construct);
PHP_METHOD(ADOdb_ResultsetIterator, seek);
PHP_METHOD(ADOdb_ResultsetIterator, current);
PHP_METHOD(ADOdb_ResultsetIterator, key);
PHP_METHOD(ADOdb_ResultsetIterator, next);
PHP_METHOD(ADOdb_ResultsetIterator, rewind);
PHP_METHOD(ADOdb_ResultsetIterator, valid);
PHP_METHOD(ADOdb_ResultsetIterator, __call);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultsetiterator___construct, 0, 0, 1)
  ZEND_ARG_INFO(0, rs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultsetiterator_seek, 0, 0, 1)
  ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_resultsetiterator___call, 0, 0, 2)
  ZEND_ARG_INFO(0, func)
  ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_resultsetiterator_method_entry) {
	PHP_ME(ADOdb_ResultsetIterator, __construct, arginfo_adodb_resultsetiterator___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_ResultsetIterator, seek, arginfo_adodb_resultsetiterator_seek, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_ResultsetIterator, __call, arginfo_adodb_resultsetiterator___call, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
