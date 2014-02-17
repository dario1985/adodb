
extern zend_class_entry *adodb_driver_cache_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_read, 0, 0, 2)
  ZEND_ARG_INFO(0, key)
  ZEND_ARG_INFO(0, ttl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_write, 0, 0, 3)
  ZEND_ARG_INFO(0, key)
  ZEND_ARG_INFO(0, value)
  ZEND_ARG_INFO(0, ttl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_flush, 0, 0, 1)
  ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_cache_method_entry) {
	PHP_ABSTRACT_ME(ADOdb_Driver_Cache, read, arginfo_adodb_driver_cache_read)
	PHP_ABSTRACT_ME(ADOdb_Driver_Cache, write, arginfo_adodb_driver_cache_write)
	PHP_ABSTRACT_ME(ADOdb_Driver_Cache, flush, arginfo_adodb_driver_cache_flush)
	PHP_ABSTRACT_ME(ADOdb_Driver_Cache, flushAll, NULL)
  PHP_FE_END
};
