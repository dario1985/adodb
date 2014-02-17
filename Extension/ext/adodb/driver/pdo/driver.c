
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/hash.h"
#include "kernel/exception.h"
#include "kernel/array.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
/**
 * Connection and query wrapper
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_PDO_Driver) {

	ZEPHIR_REGISTER_CLASS(ADOdb\\Driver\\PDO, Driver, adodb, driver_pdo_driver, adodb_driver_pdo_driver_method_entry, 0);

/** Connection information (database name is public) */
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("dsn"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("dso"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(adodb_driver_pdo_driver_ce, SL("hostname"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(adodb_driver_pdo_driver_ce, SL("username"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(adodb_driver_pdo_driver_ce, SL("password"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(adodb_driver_pdo_driver_ce, SL("database"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(adodb_driver_pdo_driver_ce, SL("connector"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("fetchMode"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("pdo"), ZEND_ACC_PROTECTED TSRMLS_CC);
/** PDO demands fetchmodes on each resultset, so define a default */
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("fetchmode"), ZEND_ACC_PROTECTED TSRMLS_CC);
/** PDO drivers options:
     * This array holds one or more key=>value pairs to set attribute values
     * for the PDOStatement object that this method returns. You would most
     * commonly use this to set the PDO::ATTR_CURSOR value to PDO::CURSOR_SCROLL
     * to request a scrollable cursor. Some drivers have driver specific options
     * that may be set at prepare-time.
     */
	zend_declare_property_null(adodb_driver_pdo_driver_ce, SL("pdoDriverOptions"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(adodb_driver_pdo_driver_ce, SL("FETCH_DEFAULT"), 2 TSRMLS_CC);

	zend_class_implements(adodb_driver_pdo_driver_ce TSRMLS_CC, 1, adodb_driver_ce);

	return SUCCESS;

}

/**
 * Constructor: Initialise connector
 * @param connector String denoting type of database
 */
PHP_METHOD(ADOdb_Driver_PDO_Driver, __construct) {

	zend_function *_20 = NULL;
	HashTable *_18;
	HashPosition _17;
	zend_class_entry *_13;
	zend_bool _7;
	zval *dso, *_0, *_1, *_2, *_3, *_4, *_5, *_6, *_8, *_9, *_10, *_11 = NULL, *_12, *_14, *_15, *attr = NULL, *value = NULL, *_16, **_19;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dso);



	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, dso, "gettype");
	zephir_update_property_this(this_ptr, SL("connector"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, dso, "gethostname");
	zephir_update_property_this(this_ptr, SL("hostname"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	zephir_call_method(_2, dso, "getusername");
	zephir_update_property_this(this_ptr, SL("username"), _2 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method(_3, dso, "getpassword");
	zephir_update_property_this(this_ptr, SL("password"), _3 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	zephir_call_method(_4, dso, "getdatabase");
	zephir_update_property_this(this_ptr, SL("database"), _4 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_5);
	zephir_call_method(_5, dso, "getoptions");
	zephir_update_property_this(this_ptr, SL("pdoDriverOptions"), _5 TSRMLS_CC);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("connector"), PH_NOISY_CC);
	_7 = ZEPHIR_IS_STRING(_6, "sqlite");
	if (!(_7)) {
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("connector"), PH_NOISY_CC);
		_7 = ZEPHIR_IS_STRING(_8, "sqlite2");
	}
	if (_7) {
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("connector"), PH_NOISY_CC);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("database"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_11);
		ZEPHIR_CONCAT_VSV(_11, _9, ":", _10);
		zephir_update_property_this(this_ptr, SL("dsn"), _11 TSRMLS_CC);
	} else {
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("connector"), PH_NOISY_CC);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("hostname"), PH_NOISY_CC);
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("database"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_11);
		ZEPHIR_CONCAT_VSVSV(_11, _9, ":host=", _10, ";dbname=", _12);
		zephir_update_property_this(this_ptr, SL("dsn"), _11 TSRMLS_CC);
	}
	ZEPHIR_INIT_LNVAR(_11);
	_13 = zend_fetch_class(SL("PDO"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_11, _13);
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("dsn"), PH_NOISY_CC);
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("username"), PH_NOISY_CC);
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("password"), PH_NOISY_CC);
	zephir_call_method_p3_noret(_11, "__construct", _9, _10, _12);
	zephir_update_property_this(this_ptr, SL("pdo"), _11 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_14);
	ZVAL_LONG(_14, 10);
	ZEPHIR_INIT_VAR(_15);
	ZVAL_LONG(_15, 1);
	zephir_call_method_p2_noret(this_ptr, "setattribute", _14, _15);
	ZEPHIR_INIT_BNVAR(_14);
	ZVAL_LONG(_14, 3);
	ZEPHIR_INIT_BNVAR(_15);
	ZVAL_LONG(_15, 2);
	zephir_call_method_p2_noret(this_ptr, "setattribute", _14, _15);
	_16 = zephir_fetch_nproperty_this(this_ptr, SL("pdoDriverOptions"), PH_NOISY_CC);
	zephir_is_iterable(_16, &_18, &_17, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_18, (void**) &_19, &_17) == SUCCESS
	  ; zephir_hash_move_forward_ex(_18, &_17)
	) {
		ZEPHIR_GET_HMKEY(attr, _18, _17);
		ZEPHIR_GET_HVALUE(value, _19);
		zephir_call_method_p2_cache_noret(this_ptr, "setattribute", &_20, attr, value);
	}
	ZEPHIR_INIT_BNVAR(_14);
	ZVAL_LONG(_14, 2);
	zephir_call_method_p1_noret(this_ptr, "setfetchmode", _14);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, setFetchMode) {

	zval *fetchMode = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fetchMode);

	ZEPHIR_SEPARATE_PARAM(fetchMode);


	do {
		if (ZEPHIR_IS_LONG(fetchMode, 0)) {
			ZEPHIR_INIT_NVAR(fetchMode);
			ZVAL_LONG(fetchMode, 2);
			break;
		}
		if (ZEPHIR_IS_LONG(fetchMode, 2)) {
			ZEPHIR_INIT_NVAR(fetchMode);
			ZVAL_LONG(fetchMode, 2);
			break;
		}
		if (ZEPHIR_IS_LONG(fetchMode, 1)) {
			ZEPHIR_INIT_NVAR(fetchMode);
			ZVAL_LONG(fetchMode, 3);
			break;
		}
		if (ZEPHIR_IS_LONG(fetchMode, 3)) {
			ZEPHIR_INIT_NVAR(fetchMode);
			ZVAL_LONG(fetchMode, 4);
			break;
		}
		ZEPHIR_THROW_EXCEPTION_STR(adodb_connectionexception_ce, "Unsupported fetch mode value");
		return;
	} while(0);

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 19);
	zephir_call_method_p2_noret(_0, "setattribute", _1, fetchMode);
	zephir_update_property_this(this_ptr, SL("fetchMode"), fetchMode TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, setAttribute) {

	zval *attribute, *value = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &attribute, &value);

	if (!value) {
		value = ZEPHIR_GLOBAL(global_null);
	}


	zephir_update_property_array(this_ptr, SL("pdoDriverOptions"), attribute, value TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method_p2_noret(_0, "setattribute", attribute, value);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, getAttribute) {

	zval *attribute, *_0, *_1;

	zephir_fetch_params(0, 1, 0, &attribute);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdoDriverOptions"), PH_NOISY_CC);
	zephir_array_fetch(&_1, _0, attribute, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_CTORW(_1);

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, canScroll) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 10);
	zephir_call_method_p1(_0, this_ptr, "getattribute", _1);
	RETURN_MM_BOOL(ZEPHIR_IS_LONG(_0, 1));

}

/**
 * Retrieve the ID of the last insert operation
 * @return String containing last insert ID
 */
PHP_METHOD(ADOdb_Driver_PDO_Driver, getLastInsertId) {

	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &name);

	if (!name) {
		name = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "lastinsertid", name);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, inTransaction) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "intransaction");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, query) {

	zend_bool _1;
	zval *statement_param = NULL, *vars = NULL, *st, *_0, *_2;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars);

	zephir_get_strval(statement, statement_param);
	if (!vars) {
		vars = ZEPHIR_GLOBAL(global_null);
	}


	if ((Z_TYPE_P(vars) != IS_NULL)) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(st);
		zephir_call_method_p1(st, _0, "prepare", statement);
		_1 = !ZEPHIR_IS_FALSE(st);
		if (_1) {
			ZEPHIR_INIT_VAR(_2);
			zephir_call_method_p1(_2, st, "execute", vars);
			_1 = !ZEPHIR_IS_FALSE(_2);
		}
		if (_1) {
			object_init_ex(return_value, adodb_driver_pdo_statement_ce);
			zephir_call_method_p1_noret(return_value, "__construct", st);
			RETURN_MM();
		} else {
			RETURN_MM_BOOL(0);
		}
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "query", statement);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, execute) {

	zval *sql, *vars = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &sql, &vars);

	if (!vars) {
		vars = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method_p2(return_value, _0, "exec", sql, vars);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, beginTransaction) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "begintransaction");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, commit) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "commit");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, rollBack) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "rollback");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, errorCode) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "errorcode");
	RETURN_MM();

}

PHP_METHOD(ADOdb_Driver_PDO_Driver, errorInfo) {

	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("pdo"), PH_NOISY_CC);
	zephir_call_method(return_value, _0, "errorinfo");
	RETURN_MM();

}

