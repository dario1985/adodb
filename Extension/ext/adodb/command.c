
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
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Command) {

	ZEPHIR_REGISTER_CLASS(ADOdb, Command, adodb, command, adodb_command_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(adodb_command_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Run the command using connection
 *
 * @return mixed | null
 */
PHP_METHOD(ADOdb_Command, execute) {

	zval *connection, *rs;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &connection);



	if (!(zephir_is_instance_of(connection, SL("ADOdb\\Connection") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'connection' must be an instance of 'ADOdb\\Connection'");
		return;
	}
	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	ZEPHIR_INIT_VAR(rs);
	zephir_call_method(rs, this_ptr, "doquery");
	if (zephir_is_true(rs)) {
		zephir_call_method_p1(return_value, this_ptr, "processresults", rs);
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * doQuery
 *
 * @return ResultSet | null
 */
PHP_METHOD(ADOdb_Command, doQuery) {


	ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_BadMethodCallException, "Abstract method not implemented");
	return;

}

/**
 * processResults: Postprocess the results in some way
 */
PHP_METHOD(ADOdb_Command, processResults) {

	zval *rs;

	zephir_fetch_params(0, 1, 0, &rs);



	if (!(zephir_is_instance_of(rs, SL("ADOdb\\ResultSet") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_InvalidArgumentException, "Parameter 'rs' must be an instance of 'ADOdb\\ResultSet'");
		return;
	}
	ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_BadMethodCallException, "Abstract method not implemented");
	return;

}

