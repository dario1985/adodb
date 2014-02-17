
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
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_DriverManager) {

	ZEPHIR_REGISTER_CLASS(ADOdb\\Driver, DriverManager, adodb, driver_drivermanager, adodb_driver_drivermanager_method_entry, 0);


	return SUCCESS;

}

PHP_METHOD(ADOdb_Driver_DriverManager, create) {

	zval *dso, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dso);



	if (!(zephir_is_instance_of(dso, SL("ADOdb\\DataSource") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'dso' must be an instance of 'ADOdb\\DataSource'");
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, dso, "gettype");
	do {
		if (ZEPHIR_IS_STRING(_0, "mysqli") || ZEPHIR_IS_STRING(_0, "mysqlt")) {
			ZEPHIR_INIT_VAR(_1);
			ZVAL_STRING(_1, "mysql", 1);
			zephir_call_method_p1_noret(dso, "settype", _1);
		}
		if (ZEPHIR_IS_STRING(_0, "mysql") || ZEPHIR_IS_STRING(_0, "sqlite") || ZEPHIR_IS_STRING(_0, "sqlite2") || ZEPHIR_IS_STRING(_0, "pdo")) {
			object_init_ex(return_value, adodb_driver_pdo_driver_ce);
			zephir_call_method_p1_noret(return_value, "__construct", dso);
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_THROW_EXCEPTION_STR(zend_exception_get_default(TSRMLS_C), "No valid Driver found for this source");
	return;

}

