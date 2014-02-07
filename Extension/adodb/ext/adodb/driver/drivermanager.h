
extern zend_class_entry *adodb_driver_drivermanager_ce;

ZEPHIR_INIT_CLASS(ADOdb_Driver_DriverManager);

PHP_METHOD(ADOdb_Driver_DriverManager, create);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_driver_drivermanager_create, 0, 0, 1)
	ZEND_ARG_INFO(0, dso)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_driver_drivermanager_method_entry) {
	PHP_ME(ADOdb_Driver_DriverManager, create, arginfo_adodb_driver_drivermanager_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
