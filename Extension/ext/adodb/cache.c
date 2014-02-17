
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
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/exception.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Cache) {

	ZEPHIR_REGISTER_CLASS(ADOdb, Cache, adodb, cache, adodb_cache_method_entry, 0);

	zend_declare_class_constant_long(adodb_cache_ce, SL("TYPE_MEMORY"), 0 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_cache_ce, SL("TYPE_FILE"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_cache_ce, SL("TYPE_APC"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_cache_ce, SL("TYPE_LIBREDIS"), 3 TSRMLS_CC);
	zend_declare_class_constant_string(adodb_cache_ce, SL("KEY_PREFIX"), "DB_" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(ADOdb_Cache, getQueryId) {

	zval *sql_param = NULL, *params = NULL, *_0 = NULL, *_1, *_2;
	zval *sql = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &sql_param, &params);

	zephir_get_strval(sql, sql_param);
	if (!params) {
		params = ZEPHIR_GLOBAL(global_null);
	}


	if ((Z_TYPE_P(params) != IS_NULL)) {
		ZEPHIR_INIT_VAR(_0);
		zephir_fast_join_str(_0, SL(""), params TSRMLS_CC);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_VV(_1, sql, _0);
		ZEPHIR_INIT_VAR(_2);
		zephir_call_func_p1(_2, "md5", _1);
		ZEPHIR_CONCAT_SV(return_value, "DB_", _2);
		RETURN_MM();
	} else {
		ZEPHIR_INIT_NVAR(_0);
		zephir_call_func_p1(_0, "md5", sql);
		ZEPHIR_CONCAT_SV(return_value, "DB_", _0);
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Cache, create) {

	zend_class_entry *_0, *_1, *_2;
	zval *type = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &type);

	if (!type) {
		ZEPHIR_CPY_WRT(type, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(type);
	}


	if ((Z_TYPE_P(type) == IS_NULL)) {
		ZEPHIR_INIT_NVAR(type);
		ZVAL_LONG(type, 0);
	}
	do {
		if (ZEPHIR_IS_LONG(type, 0)) {
			object_init_ex(return_value, adodb_driver_cache_memory_ce);
			zephir_call_method_noret(return_value, "__construct");
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(type, 2)) {
			_0 = zend_fetch_class(SL("ADOdb\\Driver\\Cache\\APC"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
			object_init_ex(return_value, _0);
			if (zephir_has_constructor(return_value TSRMLS_CC)) {
				zephir_call_method_noret(return_value, "__construct");
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(type, 3)) {
			_1 = zend_fetch_class(SL("ADOdb\\Driver\\Cache\\Libredis"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
			object_init_ex(return_value, _1);
			if (zephir_has_constructor(return_value TSRMLS_CC)) {
				zephir_call_method_noret(return_value, "__construct");
			}
			RETURN_MM();
		}
		_2 = zend_fetch_class(SL("ADOdb\\Driver\\Cache\\File"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(return_value, _2);
		if (zephir_has_constructor(return_value TSRMLS_CC)) {
			zephir_call_method_noret(return_value, "__construct");
		}
		RETURN_MM();
	} while(0);

	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Cache, serializeStatement) {

	zval *statement, *_0, *_1, _2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &statement);



	if (!(zephir_is_instance_of(statement, SL("ADOdb\\Statement") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'statement' must be an instance of 'ADOdb\\Statement'");
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, statement, "dump");
	ZEPHIR_INIT_VAR(_1);
	zephir_call_func_p1(_1, "serialize", _0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 3);
	zephir_call_func_p2(return_value, "gzcompress", _1, &_2);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Cache, unserializeStatement) {

	zval *serializedStatement, *rawSt, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &serializedStatement);



	ZEPHIR_INIT_VAR(_0);
	zephir_call_func_p1(_0, "gzuncompress", serializedStatement);
	ZEPHIR_INIT_VAR(rawSt);
	zephir_call_func_p1(rawSt, "unserialize", _0);
	if (!ZEPHIR_IS_FALSE(rawSt)) {
		object_init_ex(return_value, adodb_driver_cache_statement_ce);
		zephir_call_method_p1_noret(return_value, "__construct", rawSt);
		RETURN_MM();
	} else {
		ZEPHIR_THROW_EXCEPTION_STR(adodb_exception_ce, "Unserialize error");
		return;
	}
	ZEPHIR_MM_RESTORE();

}

