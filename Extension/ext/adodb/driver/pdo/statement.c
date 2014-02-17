
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
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_PDO_Statement) {

	ZEPHIR_REGISTER_CLASS(ADOdb\\Driver\\PDO, Statement, adodb, driver_pdo_statement, adodb_driver_pdo_statement_method_entry, 0);

	zend_declare_property_null(adodb_driver_pdo_statement_ce, SL("timeCreated"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_pdo_statement_ce, SL("st"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_pdo_statement_ce, SL("FETCH_NUM"), 3 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_pdo_statement_ce, SL("FETCH_ASSOC"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_pdo_statement_ce, SL("FETCH_BOTH"), 4 TSRMLS_CC);

	zend_class_implements(adodb_driver_pdo_statement_ce TSRMLS_CC, 1, adodb_statement_ce);

	return SUCCESS;

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, __construct) {

	zval *statement, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &statement);



	if (!(zephir_is_instance_of(statement, SL("PDOStatement") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'statement' must be an instance of 'PDOStatement'");
		return;
	}
	zephir_update_property_this(this_ptr, SL("st"), statement TSRMLS_CC);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_func(_0, "time");
	zephir_update_property_this(this_ptr, SL("timeCreated"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, timeCreated) {


	RETURN_MEMBER(this_ptr, "timeCreated");

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, canSeek) {


	RETURN_BOOL(0);

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, close) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "closecursor");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, getColumnMeta) {

	zval *_1;
	zval *column_number = NULL, *pdo_metas, *_0, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &column_number);

	if (!column_number) {
		ZEPHIR_INIT_VAR(column_number);
		ZVAL_LONG(column_number, 0);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(pdo_metas);
	zephir_call_method_p1(pdo_metas, _0, "getcolumnmeta", column_number);
	object_init_ex(return_value, adodb_fieldobject_ce);
	ZEPHIR_INIT_VAR(_1);
	array_init_size(_1, 4);
	ZEPHIR_OBS_VAR(_2);
	zephir_array_fetch_string(&_2, pdo_metas, SL("name"), PH_NOISY TSRMLS_CC);
	zephir_array_update_string(&_1, SL("name"), &_2, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_2);
	zephir_array_fetch_string(&_2, pdo_metas, SL("len"), PH_NOISY TSRMLS_CC);
	zephir_array_update_string(&_1, SL("max_length"), &_2, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_2);
	zephir_array_fetch_string(&_2, pdo_metas, SL("native_type"), PH_NOISY TSRMLS_CC);
	zephir_array_update_string(&_1, SL("type"), &_2, PH_COPY | PH_SEPARATE);
	zephir_call_method_p1_noret(return_value, "__construct", _1);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, columnCount) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "columncount");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, dump) {

	zval *_2 = NULL;
	int col = 0;
	zval *metas, *nCols, *pdo_metas = NULL, *_0, *_1 = NULL, *_3 = NULL, *_4;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(metas);
	array_init(metas);
	ZEPHIR_INIT_VAR(nCols);
	zephir_call_method(nCols, this_ptr, "columncount");
	while (1) {
		if (!(ZEPHIR_GT_LONG(nCols, col))) {
			break;
		}
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, col);
		ZEPHIR_INIT_NVAR(pdo_metas);
		zephir_call_method_p1(pdo_metas, _0, "getcolumnmeta", _1);
		ZEPHIR_INIT_NVAR(_2);
		array_init_size(_2, 4);
		ZEPHIR_OBS_NVAR(_3);
		zephir_array_fetch_string(&_3, pdo_metas, SL("name"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_2, SL("name"), &_3, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_3);
		zephir_array_fetch_string(&_3, pdo_metas, SL("len"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_2, SL("max_length"), &_3, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_3);
		zephir_array_fetch_string(&_3, pdo_metas, SL("native_type"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_2, SL("type"), &_3, PH_COPY | PH_SEPARATE);
		zephir_array_append(&metas, _2, PH_SEPARATE);
		col++;
	}
	array_init_size(return_value, 4);
	ZEPHIR_INIT_NVAR(_1);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 3);
	zephir_call_method_p1(_1, this_ptr, "fetchall", _4);
	zephir_array_update_string(&return_value, SL("RESULTSET"), &_1, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&return_value, SL("COLUMN_META"), &metas, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_3);
	zephir_read_property_this(&_3, this_ptr, SL("timeCreated"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("CREATED"), &_3, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, errorCode) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "errorcode");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, errorInfo) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "errorinfo");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, rowCount) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "rowcount");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, execute) {

	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "execute", parameters);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, fetch) {

	zval *offset_param = NULL, *_0, *_1;
	int offset;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &offset_param);

	if (!offset_param) {
		offset = 0;
	} else {
		offset = zephir_get_intval(offset_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, offset);
	zephir_call_method_p1(return_value, _0, "fetch", _1);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, fetchAll) {

	zval *fetch_style = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &fetch_style);

	if (!fetch_style) {
		fetch_style = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "fetchall", fetch_style);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, fetchColumn) {

	zval *column_number_param = NULL, *_0, *_1;
	int column_number;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &column_number_param);

	if (!column_number_param) {
		column_number = 0;
	} else {
		column_number = zephir_get_intval(column_number_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, column_number);
	zephir_call_method_p1(return_value, _0, "fetchcolumn", _1);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Statement, setFetchMode) {

	zval *mode, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &mode);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("st"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "setfetchmode", mode);
	RETURN_MM();

}

