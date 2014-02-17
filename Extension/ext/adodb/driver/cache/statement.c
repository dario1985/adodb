
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/exception.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache_Statement) {

	ZEPHIR_REGISTER_CLASS(ADOdb\\Driver\\Cache, Statement, adodb, driver_cache_statement, adodb_driver_cache_statement_method_entry, 0);

	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("resultsetData"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("rowCount"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("columnMeta"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("columnMap"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("lastErrorCode"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("lastErrorInfo"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("currentRow"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("timeCreated"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(adodb_driver_cache_statement_ce, SL("fetchMode"), 2, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_cache_statement_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_cache_statement_ce, SL("FETCH_NUM"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_cache_statement_ce, SL("FETCH_ASSOC"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_cache_statement_ce, SL("FETCH_BOTH"), 3 TSRMLS_CC);
	zend_declare_class_constant_null(adodb_driver_cache_statement_ce, SL("FETCH_NORMAL") TSRMLS_CC);

	zend_class_implements(adodb_driver_cache_statement_ce TSRMLS_CC, 1, adodb_statement_ce);

	return SUCCESS;

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, __construct) {

	zend_bool _0;
	zval *data = NULL, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &data);

	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_array_isset_string(data, SS("COLUMN_META"));
	if (_0) {
		_0 = zephir_array_isset_string(data, SS("RESULTSET"));
	}
	if (_0) {
		zephir_array_fetch_string(&_1, data, SL("COLUMN_META"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("columnMeta"), _1 TSRMLS_CC);
		zephir_array_fetch_string(&_2, data, SL("RESULTSET"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_call_method_p1_noret(this_ptr, "initresultsetdata", _2);
		if (zephir_array_isset_string(data, SS("CREATED"))) {
			ZEPHIR_OBS_VAR(_3);
			zephir_array_fetch_string(&_3, data, SL("CREATED"), PH_NOISY TSRMLS_CC);
			ZEPHIR_INIT_ZVAL_NREF(_4);
			ZVAL_LONG(_4, zephir_get_intval(_3));
			zephir_update_property_this(this_ptr, SL("timeCreated"), _4 TSRMLS_CC);
		}
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("resultsetData"), PH_NOISY_CC);
		ZEPHIR_INIT_ZVAL_NREF(_5);
		ZVAL_LONG(_5, zephir_fast_count_int(_4 TSRMLS_CC));
		zephir_update_property_this(this_ptr, SL("rowCount"), _5 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_5);
		ZVAL_LONG(_5, 0);
		zephir_update_property_this(this_ptr, SL("currentRow"), _5 TSRMLS_CC);
	} else {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Invalid data");
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, initResultsetData) {

	HashTable *_3;
	HashPosition _2;
	zval *resultsetRawData_param = NULL, *_0, *c = NULL, *_1, **_4, *_5;
	zval *resultsetRawData = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &resultsetRawData_param);

	zephir_get_arrval(resultsetRawData, resultsetRawData_param);


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("columnMap"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("resultsetData"), resultsetRawData TSRMLS_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("columnMeta"), PH_NOISY_CC);
	zephir_is_iterable(_1, &_3, &_2, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(c, _4);
		zephir_array_fetch_string(&_5, c, SL("name"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_update_property_array_append(this_ptr, SL("columnMap"), _5 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, __destruct) {


	zephir_update_property_this(this_ptr, SL("data"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("columnMap"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("columnMeta"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, timeCreated) {


	RETURN_MEMBER(this_ptr, "timeCreated");

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, canSeek) {


	RETURN_BOOL(1);

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, close) {


	RETURN_BOOL(1);

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, errorCode) {


	RETURN_MEMBER(this_ptr, "lastErrorCode");

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, errorInfo) {


	RETURN_MEMBER(this_ptr, "lastErrorInfo");

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, execute) {

	zval *parameters;

	zephir_fetch_params(0, 1, 0, &parameters);



	RETURN_BOOL(1);

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, columnCount) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("columnMeta"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, rowCount) {


	RETURN_MEMBER(this_ptr, "rowCount");

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, fetch) {

	zval *offset = NULL, *_0, *row, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &offset);

	if (!offset) {
		ZEPHIR_CPY_WRT(offset, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(offset);
	}


	if ((Z_TYPE_P(offset) == IS_NULL)) {
		RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("currentRow") TSRMLS_CC));
		ZEPHIR_OBS_NVAR(offset);
		zephir_read_property_this(&offset, this_ptr, SL("currentRow"), PH_NOISY_CC);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rowCount"), PH_NOISY_CC);
	if (ZEPHIR_LT(offset, _0)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("resultsetData"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(row);
		zephir_array_fetch(&row, _1, offset, PH_NOISY TSRMLS_CC);
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("fetchMode"), PH_NOISY_CC);
		if (((int) (zephir_get_numberval(_2)) & 2)) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("fetchMode"), PH_NOISY_CC);
			if (((int) (zephir_get_numberval(_3)) & 1)) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("columnMap"), PH_NOISY_CC);
				ZEPHIR_INIT_VAR(_5);
				zephir_call_func_p2(_5, "array_combine", _4, row);
				zephir_fast_array_merge(return_value, &(row), &(_5) TSRMLS_CC);
				RETURN_MM();
			} else {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("columnMap"), PH_NOISY_CC);
				zephir_call_func_p2(return_value, "array_combine", _4, row);
				RETURN_MM();
			}
		} else {
			RETURN_CCTOR(row);
		}
	} else {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, fetchAll) {

	zend_function *_9 = NULL;
	HashTable *_5, *_11;
	HashPosition _4, _10;
	zval *fetch_style = NULL, *_0 = NULL, *_1, *data, *row = NULL, *_2, *_3, **_6, *_7, *_8 = NULL, **_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &fetch_style);

	if (!fetch_style) {
		ZEPHIR_CPY_WRT(fetch_style, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(fetch_style);
	}


	ZEPHIR_INIT_VAR(_0);
	if ((Z_TYPE_P(fetch_style) != IS_NULL)) {
		ZEPHIR_CPY_WRT(_0, fetch_style);
	} else {
		zephir_read_property_this(&_0, this_ptr, SL("fetchMode"), PH_NOISY_CC);
	}
	ZEPHIR_CPY_WRT(fetch_style, _0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("fetchMode"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_1)) & 2)) {
		ZEPHIR_INIT_VAR(data);
		array_init(data);
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("fetchMode"), PH_NOISY_CC);
		if (((int) (zephir_get_numberval(_2)) & 1)) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("resultsetData"), PH_NOISY_CC);
			zephir_is_iterable(_3, &_5, &_4, 0, 0);
			for (
			  ; zend_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			  ; zephir_hash_move_forward_ex(_5, &_4)
			) {
				ZEPHIR_GET_HVALUE(row, _6);
				_7 = zephir_fetch_nproperty_this(this_ptr, SL("columnMap"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_8);
				ZEPHIR_CALL_INTERNAL_FUNCTION(_8, &_8, "array_combine", &_9, 2, _7, row);
				zephir_fast_array_merge(_0, &(row), &(_8) TSRMLS_CC);
				zephir_array_append(&data, _0, PH_SEPARATE);
			}
		} else {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("resultsetData"), PH_NOISY_CC);
			zephir_is_iterable(_3, &_11, &_10, 0, 0);
			for (
			  ; zend_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
			  ; zephir_hash_move_forward_ex(_11, &_10)
			) {
				ZEPHIR_GET_HVALUE(row, _12);
				_7 = zephir_fetch_nproperty_this(this_ptr, SL("columnMap"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_8);
				ZEPHIR_CALL_INTERNAL_FUNCTION(_8, &_8, "array_combine", &_9, 2, _7, row);
				zephir_array_append(&data, _8, PH_SEPARATE);
			}
		}
		RETURN_CCTOR(data);
	} else {
		RETURN_MM_MEMBER(this_ptr, "resultsetData");
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, fetchColumn) {

	zval *column_number = NULL, *_0, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &column_number);

	if (!column_number) {
		ZEPHIR_INIT_VAR(column_number);
		ZVAL_LONG(column_number, 0);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("currentRow"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("rowCount"), PH_NOISY_CC);
	if (ZEPHIR_LT(_0, _1)) {
		RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("currentRow") TSRMLS_CC));
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("resultsetData"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(_4);
		zephir_read_property_this(&_4, this_ptr, SL("currentRow"), PH_NOISY_CC);
		zephir_array_fetch(&_3, _2, _4, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_fetch(&_5, _3, column_number, PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_5);
	} else {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, getColumnMeta) {

	zval *column_number = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &column_number);

	if (!column_number) {
		ZEPHIR_INIT_VAR(column_number);
		ZVAL_LONG(column_number, 0);
	}


	object_init_ex(return_value, adodb_fieldobject_ce);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("columnMeta"), PH_NOISY_CC);
	zephir_array_fetch(&_1, _0, column_number, PH_NOISY | PH_READONLY TSRMLS_CC);
	zephir_call_method_p1_noret(return_value, "__construct", _1);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, setFetchMode) {

	zval *mode;

	zephir_fetch_params(0, 1, 0, &mode);



	zephir_update_property_this(this_ptr, SL("fetchMode"), mode TSRMLS_CC);

}

PHP_METHOD(ADOdb_Driver_Cache_Statement, dump) {


	ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_RuntimeException, "Cannot dump a cached statement");
	return;

}

