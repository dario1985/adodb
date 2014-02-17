
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/exception.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
/**
 * Resultset Class
 */
ZEPHIR_INIT_CLASS(ADOdb_ResultSet) {

	ZEPHIR_REGISTER_CLASS(ADOdb, ResultSet, adodb, resultset, adodb_resultset_method_entry, 0);

/**
     * Cache Driver
     * @var Cache
     */
	zend_declare_property_null(adodb_resultset_ce, SL("cache"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * Statement object
     * @var Statement
     */
	zend_declare_property_null(adodb_resultset_ce, SL("statement"), ZEND_ACC_PROTECTED TSRMLS_CC);
/* Publically Readonly accessible  __get() attributes: see publicProperties */
	zend_declare_property_bool(adodb_resultset_ce, SL("p_fields"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("p_timeCreated"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(adodb_resultset_ce, SL("p_EOF"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("p_numOfRows"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("p_numOfFields"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("bufferedResults"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("canSeek"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("currentRow"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_resultset_ce, SL("publicProperties"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(adodb_resultset_ce TSRMLS_CC, 1, spl_ce_Countable);
	zend_class_implements(adodb_resultset_ce TSRMLS_CC, 1, zend_ce_aggregate);

	return SUCCESS;

}

PHP_METHOD(ADOdb_ResultSet, __construct) {

	zval *_5;
	zval *statement, *_0, *_1, *_2, *_3, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &statement);



	zephir_update_property_this(this_ptr, SL("statement"), statement TSRMLS_CC);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, statement, "timecreated");
	zephir_update_property_this(this_ptr, SL("p_timeCreated"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, statement, "canseek");
	zephir_update_property_this(this_ptr, SL("canSeek"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	zephir_call_method(_2, statement, "rowcount");
	zephir_update_property_this(this_ptr, SL("p_numOfRows"), _2 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method(_3, statement, "columncount");
	zephir_update_property_this(this_ptr, SL("p_numOfFields"), _3 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_4);
	ZVAL_LONG(_4, -1);
	zephir_update_property_this(this_ptr, SL("currentRow"), _4 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_5);
	array_init_size(_5, 7);
	add_assoc_long_ex(_5, SS("timeCreated"), 1);
	add_assoc_long_ex(_5, SS("numOfFields"), 1);
	add_assoc_long_ex(_5, SS("numOfRows"), 1);
	add_assoc_long_ex(_5, SS("fields"), 1);
	add_assoc_long_ex(_5, SS("EOF"), 1);
	zephir_update_property_this(this_ptr, SL("publicProperties"), _5 TSRMLS_CC);
	zephir_call_method_noret(this_ptr, "movenext");
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultSet, __destruct) {

	ZEPHIR_MM_GROW();

	zephir_call_method_noret(this_ptr, "close");
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultSet, __get) {

	zval *name = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);

	ZEPHIR_SEPARATE_PARAM(name);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("publicProperties"), PH_NOISY_CC);
	if (zephir_array_isset(_0, name)) {
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "p_", name);
		ZEPHIR_CPY_WRT(name, _1);
		ZEPHIR_OBS_VAR(_2);
		zephir_read_property_zval(&_2, this_ptr, name, PH_NOISY_CC);
		RETURN_CCTOR(_2);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultSet, isEOF) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("p_EOF"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_get_boolval(_0));

}

/**
 * RecordCount: Retrieve number of records in this RS
 * @return Integer number of records
 */
PHP_METHOD(ADOdb_ResultSet, recordCount) {


	RETURN_MEMBER(this_ptr, "p_numOfRows");

}

PHP_METHOD(ADOdb_ResultSet, currentRow) {


	RETURN_MEMBER(this_ptr, "currentRow");

}

/**
 * Return whole recordset as a 2-dimensional associative array if there are more than 2 columns.
 * The first column is treated as the key and is not included in the array.
 * If there is only 2 columns, it will return a 1 dimensional array of key-value pairs unless
 * force_array == true.
 *
 * @param bool force_array (Optional) has only meaning if we have 2 data columns. If false, a 1 dimensional
 * 	array is returned, otherwise a 2 dimensional array is returned. If this sounds confusing,
 * 	read the source.
 *
 * @param bool first2cols (Optional) means if there are more than 2 cols, ignore the remaining cols and
 * instead of returning array[col0] => array(remaining cols), return array[col0] => col1
 *
 * @return an associative array indexed by the first column of the array,
 * 	or false if the  data has less than 2 cols.
 */
PHP_METHOD(ADOdb_ResultSet, getAssoc) {

	zend_function *_8 = NULL, *_12 = NULL, *_14 = NULL, *_16 = NULL, *_17 = NULL;
	zend_bool useNumIndex, _2, _3;
	int cols;
	zval *force_array = NULL, *first2cols = NULL, *_0, *_1, *results, *_4, *_5, _6 = zval_used_for_init, *_7 = NULL, *_9 = NULL, *_10, *_11, *_13 = NULL, *_15, *key = NULL, *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &force_array, &first2cols);

	if (!force_array) {
		force_array = ZEPHIR_GLOBAL(global_false);
	}
	if (!first2cols) {
		first2cols = ZEPHIR_GLOBAL(global_false);
	}


	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("p_numOfFields"), PH_NOISY_CC);
	cols = zephir_get_intval(_0);
	if ((cols < 2)) {
		RETURN_MM_BOOL(0);
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
	useNumIndex = zephir_array_isset_long(_1, 0);
	ZEPHIR_INIT_VAR(results);
	array_init(results);
	_2 = ZEPHIR_IS_FALSE(first2cols);
	if (_2) {
		_3 = (cols > 2);
		if (!(_3)) {
			_3 = ZEPHIR_IS_TRUE(force_array);
		}
		_2 = _3;
	}
	if (_2) {
		if ((useNumIndex == 1)) {
			while (1) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
				if (!(!zephir_is_true(_4))) {
					break;
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				ZEPHIR_SINIT_NVAR(_6);
				ZVAL_LONG(&_6, 1);
				ZEPHIR_INIT_NVAR(_7);
				ZEPHIR_CALL_INTERNAL_FUNCTION(_7, &_7, "array_slice", &_8, 3, _5, &_6, ZEPHIR_GLOBAL(global_true));
				ZEPHIR_INIT_NVAR(_9);
				_10 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				zephir_array_fetch_long(&_11, _10, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
				zephir_fast_trim(_9, _11, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				zephir_array_update_zval(&results, _9, &_7, PH_COPY | PH_SEPARATE);
				zephir_call_method_cache_noret(this_ptr, "movenext", &_12);
			}
		} else {
			while (1) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
				if (!(!zephir_is_true(_4))) {
					break;
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				ZEPHIR_SINIT_NVAR(_6);
				ZVAL_LONG(&_6, 1);
				ZEPHIR_INIT_NVAR(_7);
				ZEPHIR_CALL_INTERNAL_FUNCTION(_7, &_7, "array_slice", &_8, 3, _5, &_6, ZEPHIR_GLOBAL(global_true));
				ZEPHIR_INIT_NVAR(_9);
				_10 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				Z_SET_ISREF_P(_10);
				ZEPHIR_INIT_NVAR(_13);
				zephir_call_func_p1(_13, "reset", _10);
				Z_UNSET_ISREF_P(_10);
				zephir_fast_trim(_9, _13, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				zephir_array_update_zval(&results, _9, &_7, PH_COPY | PH_SEPARATE);
				zephir_call_method_cache_noret(this_ptr, "movenext", &_14);
			}
		}
	} else {
		if ((useNumIndex == 1)) {
			while (1) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
				if (!(!zephir_is_true(_4))) {
					break;
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				zephir_array_fetch_long(&_11, _5, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
				ZEPHIR_INIT_NVAR(_7);
				_10 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				zephir_array_fetch_long(&_15, _10, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
				zephir_fast_trim(_7, _15, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				zephir_array_update_zval(&results, _7, &_11, PH_COPY | PH_SEPARATE);
				zephir_call_method_cache_noret(this_ptr, "movenext", &_16);
			}
		} else {
			while (1) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
				if (!(!zephir_is_true(_4))) {
					break;
				}
				ZEPHIR_INIT_NVAR(key);
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				Z_SET_ISREF_P(_5);
				ZEPHIR_INIT_NVAR(_7);
				zephir_call_func_p1(_7, "reset", _5);
				Z_UNSET_ISREF_P(_5);
				zephir_fast_trim(key, _7, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				_10 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
				Z_SET_ISREF_P(_10);
				ZEPHIR_INIT_NVAR(value);
				zephir_call_func_p1(value, "next", _10);
				Z_UNSET_ISREF_P(_10);
				zephir_array_update_zval(&results, key, &value, PH_COPY | PH_SEPARATE);
				zephir_call_method_cache_noret(this_ptr, "movenext", &_17);
			}
		}
	}
	RETURN_CCTOR(results);

}

/**
 * Fetch a row, returning false if no more rows.
 * This is PEAR DB compat mode but widely used in ADOdb apps
 *
 * @return false or array containing the current record
 */
PHP_METHOD(ADOdb_ResultSet, fetchRow) {

	zval *_0, *results;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		RETURN_MM_BOOL(0);
	} else {
		ZEPHIR_OBS_VAR(results);
		zephir_read_property_this(&results, this_ptr, SL("p_fields"), PH_NOISY_CC);
		zephir_call_method_noret(this_ptr, "movenext");
		RETURN_CCTOR(results);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Some databases allow multiple recordsets to be returned. This function
 * will return true if there is a next recordset, or false if no more.
 */
PHP_METHOD(ADOdb_ResultSet, nextRecordSet) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "nextrowset");
	RETURN_MM();

}

/**
 * Move to the first row in the recordset.
 * Many databases do NOT support this.
 *
 * @return boolean
 */
PHP_METHOD(ADOdb_ResultSet, moveFirst) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("currentRow"), PH_NOISY_CC);
	if (ZEPHIR_IS_LONG(_0, 0)) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0);
	zephir_call_method_p1(return_value, this_ptr, "move", _1);
	RETURN_MM();

}

/**
 * Move to the last row in the recordset.
 *
 * @return boolean
 */
PHP_METHOD(ADOdb_ResultSet, moveLast) {

	zval *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_0, 0)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, (zephir_get_numberval(_1) - 2));
		zephir_call_method_p1(return_value, this_ptr, "move", _2);
		RETURN_MM();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
	if (zephir_is_true(_1)) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * MoveNext: Fetch next row and check if we"re at the end
 */
PHP_METHOD(ADOdb_ResultSet, moveNext) {

	zend_bool _1;
	zval *_0, *_2, *_3, *_4, *_5, *_6, *_7, *_8;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("p_EOF"), PH_NOISY_CC);
	_1 = !zephir_is_true(_0);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("currentRow"), PH_NOISY_CC);
		_1 = ZEPHIR_GE(_2, _3);
	}
	if (_1) {
		RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("currentRow") TSRMLS_CC));
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("bufferedResults"), PH_NOISY_CC);
		if ((Z_TYPE_P(_4) == IS_NULL)) {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_6);
			zephir_call_method(_6, _5, "fetch");
			zephir_update_property_this(this_ptr, SL("p_fields"), _6 TSRMLS_CC);
		} else {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("bufferedResults"), PH_NOISY_CC);
			ZEPHIR_OBS_VAR(_8);
			zephir_read_property_this(&_8, this_ptr, SL("currentRow"), PH_NOISY_CC);
			zephir_array_fetch(&_7, _5, _8, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("p_fields"), _7 TSRMLS_CC);
		}
		RETURN_MM_BOOL(1);
	} else {
		zephir_update_property_this(this_ptr, SL("p_fields"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("p_EOF"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Move: Random access to a specific row in the recordset.
 * Some databases do not support
 * access to previous rows in the databases (no scrolling backwards).
 *
 * @param rowNumber is the row to move to (0-based)
 *
 * @return true if there still rows available,
 *         or false if there are no more rows (EOF).
 */
PHP_METHOD(ADOdb_ResultSet, move) {

	zend_bool _1;
	zval *rowNumber = NULL, *_0, *_2, *_3, *fields = NULL, *_4, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &rowNumber);

	if (!rowNumber) {
		ZEPHIR_INIT_VAR(rowNumber);
		ZVAL_LONG(rowNumber, 0);
	} else {
		ZEPHIR_SEPARATE_PARAM(rowNumber);
	}


	zephir_update_property_this(this_ptr, SL("p_EOF"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
	_1 = ZEPHIR_GT_LONG(_0, 0);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
		_1 = ZEPHIR_GE(rowNumber, _2);
	}
	if (_1) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("p_numOfRows"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(rowNumber);
		ZVAL_LONG(rowNumber, (zephir_get_numberval(_3) - 2));
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("currentRow"), PH_NOISY_CC);
	if (ZEPHIR_IS_EQUAL(rowNumber, _3)) {
		RETURN_MM_BOOL(1);
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("canSeek"), PH_NOISY_CC);
	if (zephir_is_true(_3)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(fields);
		zephir_call_method_p1(fields, _4, "fetch", rowNumber);
	} else {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("bufferedResults"), PH_NOISY_CC);
		if ((Z_TYPE_P(_3) == IS_NULL)) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_5);
			zephir_call_method(_5, _4, "fetchall");
			zephir_update_property_this(this_ptr, SL("bufferedResults"), _5 TSRMLS_CC);
		}
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("bufferedResults"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(fields);
		zephir_array_fetch(&fields, _6, rowNumber, PH_NOISY TSRMLS_CC);
	}
	if (zephir_is_true(fields)) {
		zephir_update_property_this(this_ptr, SL("p_fields"), fields TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("currentRow"), rowNumber TSRMLS_CC);
		RETURN_MM_BOOL(1);
	}
	zephir_update_property_this(this_ptr, SL("p_fields"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("p_EOF"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_MM_BOOL(0);

}

/**
 * Get the value of a field in the current row by column name.
 * Will not work if ADODB_FETCH_MODE is set to ADODB_FETCH_NUM.
 *
 * @param colname  is the field to access
 *
 * @return the value of colname column
 */
PHP_METHOD(ADOdb_ResultSet, fields) {

	zval *colname, *_0, *_1;

	zephir_fetch_params(0, 1, 0, &colname);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("p_fields"), PH_NOISY_CC);
	zephir_array_fetch(&_1, _0, colname, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * Get the FieldObjects of all columns in an array.
 *
 */
PHP_METHOD(ADOdb_ResultSet, fieldTypesArray) {

	zend_function *_4 = NULL;
	zend_bool _0;
	int i = 0, _1, _2;
	zval *fields, *max, *_3 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(fields);
	array_init(fields);
	ZEPHIR_INIT_VAR(max);
	zephir_call_method(max, this_ptr, "fieldcount");
	_2 = (zephir_get_numberval(max) - 1);
	_1 = 0;
	_0 = 0;
	if ((_1 <= _2)) {
		while (1) {
			if (_0) {
				_1++;
				if (!((_1 <= _2))) {
					break;
				}
			} else {
				_0 = 1;
			}
			i = _1;
			ZEPHIR_INIT_NVAR(_3);
			zephir_call_method_cache(_3, this_ptr, "fetchfield", &_4);
			zephir_array_append(&fields, _3, PH_SEPARATE);
		}
	}
	RETURN_CCTOR(fields);

}

PHP_METHOD(ADOdb_ResultSet, fetchField) {

	zval *column_number = NULL, *field, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &column_number);

	if (!column_number) {
		ZEPHIR_INIT_VAR(column_number);
		ZVAL_LONG(column_number, 0);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(field);
	zephir_call_method_p1(field, _0, "getcolumnmeta", column_number);
	if (!ZEPHIR_IS_FALSE(field)) {
		RETURN_CCTOR(field);
	} else {
		ZEPHIR_THROW_EXCEPTION_STR(zend_exception_get_default(TSRMLS_C), "Driver don\"t support Column Meta Data");
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * @return the number of columns in the recordset.
 * Some databases will set this to 0
 * if no records are returned, others will return
 * the number of columns in the query.
 */
PHP_METHOD(ADOdb_ResultSet, fieldCount) {


	RETURN_MEMBER(this_ptr, "p_numOfFields");

}

/**
 * Return ResultSetIterator
 * @return RecordsetIterator
 */
PHP_METHOD(ADOdb_ResultSet, getIterator) {

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, adodb_resultsetiterator_ce);
	zephir_call_method_p1_noret(return_value, "__construct", this_ptr);
	RETURN_MM();

}

/**
 * Return RecordCount
 * @return int Row Count
 */
PHP_METHOD(ADOdb_ResultSet, count) {


	RETURN_MEMBER(this_ptr, "p_numOfRows");

}

PHP_METHOD(ADOdb_ResultSet, close) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
	if ((Z_TYPE_P(_0) != IS_NULL)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("statement"), PH_NOISY_CC);
		zephir_call_method(return_value, _1, "close");
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

