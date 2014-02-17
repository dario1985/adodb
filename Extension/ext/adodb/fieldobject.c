
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/array.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
/**
 * Table field information wrapper
 */
ZEPHIR_INIT_CLASS(ADOdb_FieldObject) {

	ZEPHIR_REGISTER_CLASS(ADOdb, FieldObject, adodb, fieldobject, adodb_fieldobject_method_entry, 0);

	zend_declare_property_null(adodb_fieldobject_ce, SL("name"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_fieldobject_ce, SL("max_length"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_fieldobject_ce, SL("type"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(adodb_fieldobject_ce, SL("not_null"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(adodb_fieldobject_ce, SL("has_default"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_fieldobject_ce, SL("default_value"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(ADOdb_FieldObject, __get) {

	zval *name, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_zval(&_0, this_ptr, name, PH_NOISY_CC);
	RETURN_CCTOR(_0);

}

PHP_METHOD(ADOdb_FieldObject, __set) {

	zval *name, *value = NULL;

	zephir_fetch_params(0, 1, 1, &name, &value);

	if (!value) {
		value = ZEPHIR_GLOBAL(global_null);
	}


	zephir_update_property_zval_zval(this_ptr, name, value TSRMLS_CC);

}

PHP_METHOD(ADOdb_FieldObject, __construct) {

	HashTable *_1;
	HashPosition _0;
	zval *fieldMetaData = NULL, *attr = NULL, *value = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &fieldMetaData);

	if (!fieldMetaData) {
		fieldMetaData = ZEPHIR_GLOBAL(global_null);
	}


	if (zephir_is_true(fieldMetaData)) {
		zephir_is_iterable(fieldMetaData, &_1, &_0, 0, 0);
		for (
		  ; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(attr, _1, _0);
			ZEPHIR_GET_HVALUE(value, _2);
			zephir_update_property_zval_zval(this_ptr, attr, value TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_FieldObject, __toArray) {

	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	array_init_size(return_value, 8);
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("name"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("name"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("max_length"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("max_length"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("type"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("type"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("not_null"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("not_null"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("has_default"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("has_default"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("default_value"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("default_value"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

