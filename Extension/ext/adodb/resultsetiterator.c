
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


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
/**
 * ResultsetIterator
 * 
 * Implementing 
 */
ZEPHIR_INIT_CLASS(ADOdb_ResultsetIterator) {

	ZEPHIR_REGISTER_CLASS(ADOdb, ResultsetIterator, adodb, resultsetiterator, adodb_resultsetiterator_method_entry, 0);

/**
     * ResultSet Object
     * @var ResultSet
     */
	zend_declare_property_null(adodb_resultsetiterator_ce, SL("rs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(adodb_resultsetiterator_ce TSRMLS_CC, 1, spl_ce_SeekableIterator);

	return SUCCESS;

}

PHP_METHOD(ADOdb_ResultsetIterator, __construct) {

	zval *rs;

	zephir_fetch_params(0, 1, 0, &rs);



	zephir_update_property_this(this_ptr, SL("rs"), rs TSRMLS_CC);

}

PHP_METHOD(ADOdb_ResultsetIterator, seek) {

	zval *position, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &position);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	zephir_call_method_p1_noret(_0, "move", position);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultsetIterator, current) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property(&_1, _0, SL("fields"), PH_NOISY_CC);
	RETURN_CCTOR(_1);

}

PHP_METHOD(ADOdb_ResultsetIterator, key) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property(&_1, _0, SL("currentRow"), PH_NOISY_CC);
	RETURN_CCTOR(_1);

}

PHP_METHOD(ADOdb_ResultsetIterator, next) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	zephir_call_method_noret(_0, "movenext");
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultsetIterator, rewind) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	zephir_call_method_noret(_0, "movefirst");
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_ResultsetIterator, valid) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rs"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, _0, "iseof");
	RETURN_MM_BOOL(!zephir_is_true(_1));

}

PHP_METHOD(ADOdb_ResultsetIterator, __call) {

	zval *_0;
	zval *func, *params, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &func, &params);



	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("rs"), PH_NOISY_CC);
	zephir_array_fast_append(_0, _1);
	zephir_array_fast_append(_0, func);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _0, params);
	RETURN_MM();

}

