
extern zend_class_entry *adodb_driver_cache_memory_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache_Memory);

PHP_METHOD(ADOdb_Driver_Cache_Memory, __construct);
PHP_METHOD(ADOdb_Driver_Cache_Memory, read);
PHP_METHOD(ADOdb_Driver_Cache_Memory, write);
PHP_METHOD(ADOdb_Driver_Cache_Memory, flush);
PHP_METHOD(ADOdb_Driver_Cache_Memory, flushAll);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_memory_read, 0, 0, 2)
  ZEND_ARG_INFO(0, key)
  ZEND_ARG_INFO(0, ttl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_memory_write, 0, 0, 3)
  ZEND_ARG_INFO(0, key)
  ZEND_ARG_INFO(0, value)
  ZEND_ARG_INFO(0, ttl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_cache_memory_flush, 0, 0, 1)
  ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_cache_memory_method_entry) {
	PHP_ME(ADOdb_Driver_Cache_Memory, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_Driver_Cache_Memory, read, arginfo_adodb_driver_cache_memory_read, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Memory, write, arginfo_adodb_driver_cache_memory_write, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Memory, flush, arginfo_adodb_driver_cache_memory_flush, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_Driver_Cache_Memory, flushAll, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
