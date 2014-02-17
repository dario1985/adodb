
extern zend_class_entry *adodb_fieldobject_ce;

ZEPHIR_INIT_CLASS(ADOdb_FieldObject);

PHP_METHOD(ADOdb_FieldObject, __get);
PHP_METHOD(ADOdb_FieldObject, __set);
PHP_METHOD(ADOdb_FieldObject, __construct);
PHP_METHOD(ADOdb_FieldObject, __toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_fieldobject___get, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_fieldobject___set, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_fieldobject___construct, 0, 0, 0)
  ZEND_ARG_INFO(0, fieldMetaData)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_fieldobject_method_entry) {
	PHP_ME(ADOdb_FieldObject, __get, arginfo_adodb_fieldobject___get, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_FieldObject, __set, arginfo_adodb_fieldobject___set, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_FieldObject, __construct, arginfo_adodb_fieldobject___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_FieldObject, __toArray, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
