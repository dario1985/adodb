
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/exception.h"
#include "kernel/array.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Connection) {

	ZEPHIR_REGISTER_CLASS(ADOdb, Connection, adodb, connection, adodb_connection_method_entry, 0);

	zend_declare_property_null(adodb_connection_ce, SL("dso"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * @var Driver
     */
	zend_declare_property_null(adodb_connection_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(adodb_connection_ce, SL("debug"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_connection_ce, SL("cache"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(adodb_connection_ce, SL("FETCH_DEFAULT"), 0 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_connection_ce, SL("FETCH_NUM"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_connection_ce, SL("FETCH_ASSOC"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(adodb_connection_ce, SL("FETCH_BOTH"), 3 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(ADOdb_Connection, __construct) {

	zval *dsn_param = NULL, *_0;
	zval *dsn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &dsn_param);

	if (!dsn_param) {
		ZEPHIR_INIT_VAR(dsn);
		ZVAL_STRING(dsn, "", 1);
	} else {
		zephir_get_strval(dsn, dsn_param);
	}


	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, adodb_datasource_ce);
	zephir_call_method_p1_noret(_0, "__construct", dsn);
	zephir_update_property_this(this_ptr, SL("dso"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, __destruct) {

	ZEPHIR_MM_GROW();

	zephir_call_method_noret(this_ptr, "close");
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, __set) {

	zval *name_param = NULL, *value, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	do {
		if (ZEPHIR_IS_STRING(name, "host")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method_p1_noret(_0, "sethostname", value);
			break;
		}
		if (ZEPHIR_IS_STRING(name, "database")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method_p1_noret(_0, "setdatabase", value);
			break;
		}
		if (ZEPHIR_IS_STRING(name, "user")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method_p1_noret(_0, "setusername", value);
			break;
		}
		if (ZEPHIR_IS_STRING(name, "password")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method_p1_noret(_0, "setpassword", value);
			break;
		}
		if (ZEPHIR_IS_STRING(name, "debug")) {
			zephir_call_method_p1_noret(this_ptr, "setdebug", value);
			break;
		}
	} while(0);

	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, __get) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	do {
		if (ZEPHIR_IS_STRING(name, "host")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method(return_value, _0, "gethostname");
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(name, "database")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method(return_value, _0, "getdatabase");
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(name, "user")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method(return_value, _0, "getusername");
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(name, "password")) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
			zephir_call_method(return_value, _0, "getpassword");
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(name, "debug")) {
			RETURN_MM_MEMBER(this_ptr, "debug");
		}
	} while(0);

	ZEPHIR_MM_RESTORE();

}

/**
 * Connect: Establish connection to a database
 * @param string hostname Hostname[:port] overriding datasource specs [optional]
 * @param string username Username overriding datasource specs  [optional]
 * @param string passname Password overriding datasource specs [optional]
 * @param string database Database name overriding datasource specsString [optional]
 * @return boolean
 */
PHP_METHOD(ADOdb_Connection, connect) {

	zend_function *_6 = NULL;
	HashTable *_4;
	HashPosition _3;
	zval *hostname_param = NULL, *username_param = NULL, *password_param = NULL, *database_param = NULL, *options = NULL, *_0, *_1, *_2, *option = NULL, *value = NULL, **_5;
	zval *hostname = NULL, *username = NULL, *password = NULL, *database = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 5, &hostname_param, &username_param, &password_param, &database_param, &options);

	if (!hostname_param) {
		ZEPHIR_INIT_VAR(hostname);
		ZVAL_EMPTY_STRING(hostname);
	} else {
		zephir_get_strval(hostname, hostname_param);
	}
	if (!username_param) {
		ZEPHIR_INIT_VAR(username);
		ZVAL_EMPTY_STRING(username);
	} else {
		zephir_get_strval(username, username_param);
	}
	if (!password_param) {
		ZEPHIR_INIT_VAR(password);
		ZVAL_EMPTY_STRING(password);
	} else {
		zephir_get_strval(password, password_param);
	}
	if (!database_param) {
		ZEPHIR_INIT_VAR(database);
		ZVAL_EMPTY_STRING(database);
	} else {
		zephir_get_strval(database, database_param);
	}
	if (!options) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		RETURN_MM_BOOL(0);
	}
	if (hostname && Z_STRLEN_P(hostname)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
		zephir_call_method_p1_noret(_1, "sethostname", hostname);
	}
	if (username && Z_STRLEN_P(username)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
		zephir_call_method_p1_noret(_1, "setusername", username);
	}
	if (password && Z_STRLEN_P(password)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
		zephir_call_method_p1_noret(_1, "setpassword", password);
	}
	if (database && Z_STRLEN_P(database)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
		zephir_call_method_p1_noret(_1, "setdatabase", database);
	}
	ZEPHIR_INIT_VAR(_2);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
	zephir_call_static_p1(_2, "ADOdb\\Driver\\DriverManager", "create", _1);
	zephir_update_property_this(this_ptr, SL("connection"), _2 TSRMLS_CC);
	zephir_is_iterable(options, &_4, &_3, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HMKEY(option, _4, _3);
		ZEPHIR_GET_HVALUE(value, _5);
		zephir_call_method_p2_cache_noret(this_ptr, "setattribute", &_6, option, value);
	}
	RETURN_MM_BOOL(1);

}

/**
 * Close connection
 */
PHP_METHOD(ADOdb_Connection, close) {


	zephir_update_property_this(this_ptr, SL("connection"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);

}

PHP_METHOD(ADOdb_Connection, setDebug) {

	zval *flag;

	zephir_fetch_params(0, 1, 0, &flag);



	zephir_update_property_this(this_ptr, SL("debug"), (zephir_get_boolval(flag)) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

PHP_METHOD(ADOdb_Connection, setAttribute) {

	zval *name_param = NULL, *value, *_0, *_1;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
		zephir_call_method_p2_noret(_1, "setattribute", name, value);
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
	zephir_call_method_p2_noret(_1, "setoption", name, value);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, getAttribute) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dso"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "getoption", name);
	RETURN_MM();

}

PHP_METHOD(ADOdb_Connection, setCache) {

	zval *cache;

	zephir_fetch_params(0, 1, 0, &cache);



	if (!(zephir_is_instance_of(cache, SL("ADOdb\\ADOdb\\Cache") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_InvalidArgumentException, "Parameter 'cache' must be an instance of 'ADOdb\\ADOdb\\Cache'");
		return;
	}
	zephir_update_property_this(this_ptr, SL("cache"), cache TSRMLS_CC);

}

/**
 * Start new transaction
 *
 * @return type
 */
PHP_METHOD(ADOdb_Connection, startTrans) {

	zval *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, _0, "intransaction");
	if (!zephir_is_true(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
		zephir_call_method(return_value, _2, "begintransaction");
		RETURN_MM();
	} else {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Complete transaction
 *
 * @param type success
 * @return boolean
 */
PHP_METHOD(ADOdb_Connection, completeTrans) {

	zval *success_param = NULL, *_0, *_1, *_2;
	zend_bool success;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &success_param);

	if (!success_param) {
		success = 1;
	} else {
		success = zephir_get_boolval(success_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, _0, "intransaction");
	if (!zephir_is_true(_1)) {
		RETURN_MM_BOOL(0);
	}
	if (success) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
		zephir_call_method_noret(_2, "commit");
	} else {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
		zephir_call_method_noret(_2, "rollback");
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * GetRow: return array of value of first row
 *
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array
 */
PHP_METHOD(ADOdb_Connection, getRow) {

	zval *vars = NULL;
	zval *statement, *vars_param = NULL, *st, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement, &vars_param);

	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p2(st, this_ptr, "query", statement, vars);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_call_method_p1(return_value, st, "fetch", _0);
	RETURN_MM();

}

/**
 * CacheGetRow: cached GetRow
 *
 * @param int timeout count of seconds for cache expiry
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array
 */
PHP_METHOD(ADOdb_Connection, cacheGetRow) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *st, *_0;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, timeout);
	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p3(st, this_ptr, "cachequery", _0, statement, vars);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_call_method_p1(return_value, st, "fetch", _0);
	RETURN_MM();

}

/**
 * GetOne: return first value of first row
 *
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return mixed
 */
PHP_METHOD(ADOdb_Connection, getOne) {

	zval *vars = NULL;
	zval *statement_param = NULL, *vars_param = NULL, *st, *_0;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars_param);

	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p2(st, this_ptr, "query", statement, vars);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_call_method_p1(return_value, st, "fetchcolumn", _0);
	RETURN_MM();

}

/**
 * CacheGetOne: cached GetOne
 *
 * @param int timeout count of seconds for cache expiry
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return mixed
 */
PHP_METHOD(ADOdb_Connection, cacheGetOne) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *st, *_0;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, timeout);
	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p3(st, this_ptr, "cachequery", _0, statement, vars);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_call_method_p1(return_value, st, "fetchcolumn", _0);
	RETURN_MM();

}

/**
 * GetCol: return array of value of first column
 *
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array
 */
PHP_METHOD(ADOdb_Connection, getCol) {

	zval *vars = NULL;
	zval *statement_param = NULL, *vars_param = NULL, *col, *val = NULL, *st, *_0 = NULL;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars_param);

	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p2(st, this_ptr, "query", statement, vars);
	ZEPHIR_INIT_VAR(col);
	array_init(col);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_INIT_VAR(val);
	zephir_call_method_p1(val, st, "fetchcolumn", _0);
	while (1) {
		if (!(zephir_is_true(val))) {
			break;
		}
		zephir_array_append(&col, val, PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 0);
		ZEPHIR_INIT_NVAR(val);
		zephir_call_method_p1(val, st, "fetchcolumn", _0);
	}
	RETURN_CCTOR(col);

}

/**
 * CacheGetCol: cached GetCol
 * @param int timeout count of seconds for cache expiry
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array
 */
PHP_METHOD(ADOdb_Connection, cacheGetCol) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *col, *val = NULL, *st, *_0 = NULL;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, timeout);
	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p3(st, this_ptr, "cachequery", _0, statement, vars);
	ZEPHIR_INIT_VAR(col);
	array_init(col);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_INIT_VAR(val);
	zephir_call_method_p1(val, st, "fetchcolumn", _0);
	while (1) {
		if (!(zephir_is_true(val))) {
			break;
		}
		zephir_array_append(&col, val, PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 0);
		ZEPHIR_INIT_NVAR(val);
		zephir_call_method_p1(val, st, "fetchcolumn", _0);
	}
	RETURN_CCTOR(col);

}

/**
 * GetAll: return array of results
 *
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array Array of results
 */
PHP_METHOD(ADOdb_Connection, getAll) {

	zval *vars = NULL;
	zval *statement_param = NULL, *vars_param = NULL, *st;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars_param);

	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p2(st, this_ptr, "query", statement, vars);
	zephir_call_method(return_value, st, "fetchall");
	RETURN_MM();

}

/**
 * CacheGetAll: cached GetAll
 *
 * @param int timeout count of seconds for cache expiry
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return array Array of results
 */
PHP_METHOD(ADOdb_Connection, cacheGetAll) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *st, *_0;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, timeout);
	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p3(st, this_ptr, "cachequery", _0, statement, vars);
	zephir_call_method(return_value, st, "fetchall");
	RETURN_MM();

}

/**
 * CacheExecute
 *
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return ResultSet|false object or false if fail
 */
PHP_METHOD(ADOdb_Connection, execute) {

	zval *vars = NULL;
	zval *statement_param = NULL, *vars_param = NULL, *st;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars_param);

	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	ZEPHIR_INIT_VAR(st);
	zephir_call_method_p2(st, this_ptr, "query", statement, vars);
	if (!ZEPHIR_IS_FALSE(st)) {
		object_init_ex(return_value, adodb_resultset_ce);
		zephir_call_method_p1_noret(return_value, "__construct", st);
		RETURN_MM();
	} else {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * CacheExecute: cached Execute
 *
 * @param int timeout count of seconds for cache expiry
 * @param string statement String query to execute
 * @param array vars Array of variables to bind [optional]
 * @return ResultSet|null object or false if fail
 */
PHP_METHOD(ADOdb_Connection, cacheExecute) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *_0, *_1;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	object_init_ex(return_value, adodb_resultset_ce);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, timeout);
	zephir_call_method_p3(_0, this_ptr, "cachequery", _1, statement, vars);
	zephir_call_method_p1_noret(return_value, "__construct", _0);
	RETURN_MM();

}

/**
 * Run a command that will talk to the connection
 *
 * @param Command command
 * @return boolean
 */
PHP_METHOD(ADOdb_Connection, execCommand) {

	zval *command;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &command);



	if (!(zephir_is_instance_of(command, SL("ADOdb\\Command") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'command' must be an instance of 'ADOdb\\Command'");
		return;
	}
	zephir_call_method_p1(return_value, command, "execute", this_ptr);
	RETURN_MM();

}

/**
 * @param int fetchMode
 * @return type
 * @throws ConnectionException
 */
PHP_METHOD(ADOdb_Connection, setFetchMode) {

	zval *fetchMode, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fetchMode);



	zephir_call_method_noret(this_ptr, "checkconnected");
	do {
		if (ZEPHIR_IS_LONG(fetchMode, 0) || ZEPHIR_IS_LONG(fetchMode, 2) || ZEPHIR_IS_LONG(fetchMode, 1) || ZEPHIR_IS_LONG(fetchMode, 3)) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
			zephir_call_method_p1(return_value, _0, "setfetchmode", fetchMode);
			RETURN_MM();
		}
		ZEPHIR_THROW_EXCEPTION_STR(adodb_connectionexception_ce, "Invalid fetch mode value");
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

}

/**
 * @param string statement query statement
 * @param array vars [optional]
 * @return Statement object
 */
PHP_METHOD(ADOdb_Connection, query) {

	zval *vars = NULL;
	zval *statement_param = NULL, *vars_param = NULL, *_0;
	zval *statement = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &statement_param, &vars_param);

	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	zephir_call_method_noret(this_ptr, "checkconnected");
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	zephir_call_method_p2(return_value, _0, "query", statement, vars);
	RETURN_MM();

}

/**
 * @param int timeout
 * @param string statement query statement
 * @param array vars [optional]
 * @return Statement object
 * @throws ConnectionException
 */
PHP_METHOD(ADOdb_Connection, cacheQuery) {

	zval *vars = NULL;
	zval *statement = NULL;
	zval *timeout_param = NULL, *statement_param = NULL, *vars_param = NULL, *_0, *queryId, *st = NULL, *_1, *_2, *_3 = NULL, *_4, *_5, _6, _7;
	int timeout;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &timeout_param, &statement_param, &vars_param);

	timeout = zephir_get_intval(timeout_param);
	zephir_get_strval(statement, statement_param);
	if (!vars_param) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	} else {
		zephir_get_arrval(vars, vars_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("cache"), PH_NOISY_CC);
	if ((Z_TYPE_P(_0) != IS_NULL)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("cache"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(queryId);
		zephir_call_method_p2(queryId, _1, "getqueryid", statement, vars);
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("cache"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, timeout);
		ZEPHIR_INIT_VAR(st);
		zephir_call_method_p2(st, _2, "read", queryId, _3);
		if (!zephir_is_true(st)) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "Cache miss!", 1);
			zephir_call_method_p1_noret(this_ptr, "debug", _3);
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(st);
			zephir_call_method_p2(st, _4, "query", statement, vars);
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("cache"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_LONG(_3, timeout);
			zephir_call_method_p3_noret(_5, "write", queryId, st, _3);
		}
		RETURN_CCTOR(st);
	} else {
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "No cache engine found!", 0);
		ZEPHIR_SINIT_VAR(_7);
		ZVAL_LONG(&_7, 512);
		zephir_call_func_p2_noret("user_error", &_6, &_7);
		zephir_call_method_p2(return_value, this_ptr, "query", statement, vars);
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, debug) {

	zval *msg_param = NULL, *_0, *_1, _2;
	zval *msg = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &msg_param);

	if (!msg_param) {
		ZEPHIR_INIT_VAR(msg);
		ZVAL_STRING(msg, "", 1);
	} else {
		zephir_get_strval(msg, msg_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("debug"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE(_0)) {
		ZEPHIR_INIT_VAR(_1);
		zephir_call_func(_1, "memory_get_usage");
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_STRING(&_2, "% 10d: %s\n", 0);
		zephir_call_func_p3_noret("printf", &_2, _1, msg);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_Connection, checkConnected) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	if (!zephir_is_true(_0)) {
		ZEPHIR_THROW_EXCEPTION_STRW(adodb_connectionexception_ce, "No connected!");
		return;
	}

}

