
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/exception.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache_Memory) {

	ZEPHIR_REGISTER_CLASS_EX(ADOdb\\Driver\\Cache, Memory, adodb, driver_cache_memory, adodb_cache_ce, adodb_driver_cache_memory_method_entry, 0);

	zend_declare_property_null(adodb_driver_cache_memory_ce, SL("_cache"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(adodb_driver_cache_memory_ce TSRMLS_CC, 1, adodb_driver_cache_ce);

	return SUCCESS;

}

PHP_METHOD(ADOdb_Driver_Cache_Memory, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_cache"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Memory, read) {

	zval *key, *ttl, *_0, *st, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key, &ttl);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_cache"), PH_NOISY_CC);
	if (zephir_array_isset(_0, key)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_cache"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, key, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_VAR(st);
		zephir_call_method_p1(st, this_ptr, "unserializestatement", _2);
		if (zephir_is_instance_of(st, SL("ADOdb\\Statement") TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(_3);
			zephir_call_func(_3, "time");
			ZEPHIR_INIT_VAR(_4);
			zephir_call_method(_4, st, "timecreated");
			ZEPHIR_INIT_VAR(_5);
			sub_function(_5, _3, _4 TSRMLS_CC);
			if (ZEPHIR_GT(_5, ttl)) {
				zephir_call_method_p1_noret(this_ptr, "flush", key);
				RETURN_MM_BOOL(0);
			} else {
				RETURN_CCTOR(st);
			}
		} else {
			ZEPHIR_THROW_EXCEPTION_STR(adodb_exception_ce, "ADOdb Cache RedisLib: Cache is corrupted");
			return;
		}
	} else {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Memory, write) {

	zval *key, *value, *ttl, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &key, &value, &ttl);



	if (!(zephir_is_instance_of(value, SL("ADOdb\\Statement") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'value' must be an instance of 'ADOdb\\Statement'");
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method_p1(_0, this_ptr, "serializestatement", value);
	zephir_update_property_array(this_ptr, SL("_cache"), key, _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_Cache_Memory, flush) {

	zval *key, *_0;

	zephir_fetch_params(0, 1, 0, &key);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_cache"), PH_NOISY_CC);
	zephir_array_unset(&_0, key, 0);

}

PHP_METHOD(ADOdb_Driver_Cache_Memory, flushAll) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_cache"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

