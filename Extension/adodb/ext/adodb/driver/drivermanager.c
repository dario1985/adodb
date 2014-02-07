
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(ADOdb_Driver_DriverManager) {

	ZEPHIR_REGISTER_CLASS(ADOdb\\Driver, DriverManager, adodb, driver_drivermanager, adodb_driver_drivermanager_method_entry, 0);


	return SUCCESS;

}

PHP_METHOD(ADOdb_Driver_DriverManager, create) {

	zend_class_entry *_3;
	zval *dso, *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dso);



	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, dso, "gettype");
	do {
		if (ZEPHIR_IS_STRING(_0, "mysqli") || ZEPHIR_IS_STRING(_0, "mysqlt")) {
			ZEPHIR_INIT_VAR(_1);
			ZVAL_STRING(_1, "mysql", 1);
			zephir_call_method_p1_noret(dso, "settype", _1);
		}
		if (ZEPHIR_IS_STRING(_0, "mysql") || ZEPHIR_IS_STRING(_0, "pdo")) {
			object_init_ex(return_value, adodb_driver_pdo_driver_ce);
			if (zephir_has_constructor(return_value TSRMLS_CC)) {
				zephir_call_method_p1_noret(return_value, "__construct", dso);
			}
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(_2);
	_3 = zend_fetch_class(SL("Exception"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_2, _3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "No valid Driver found for this source", 1);
	zephir_call_method_p1_noret(_2, "__construct", _1);
	zephir_throw_exception(_2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

