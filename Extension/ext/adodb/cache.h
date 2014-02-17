
extern zend_class_entry *adodb_cache_ce;

ZEPHIR_INIT_CLASS(ADOdb_Cache);

PHP_METHOD(ADOdb_Cache, getQueryId);
PHP_METHOD(ADOdb_Cache, create);
PHP_METHOD(ADOdb_Cache, serializeStatement);
PHP_METHOD(ADOdb_Cache, unserializeStatement);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_cache_getqueryid, 0, 0, 1)
  ZEND_ARG_INFO(0, sql)
  ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_cache_create, 0, 0, 0)
  ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_cache_serializestatement, 0, 0, 1)
  ZEND_ARG_INFO(0, statement)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_cache_unserializestatement, 0, 0, 1)
  ZEND_ARG_INFO(0, serializedStatement)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_cache_method_entry) {
	PHP_ME(ADOdb_Cache, getQueryId, arginfo_adodb_cache_getqueryid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(ADOdb_Cache, create, arginfo_adodb_cache_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(ADOdb_Cache, serializeStatement, arginfo_adodb_cache_serializestatement, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(ADOdb_Cache, unserializeStatement, arginfo_adodb_cache_unserializestatement, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
