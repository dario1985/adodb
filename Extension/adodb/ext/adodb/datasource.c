
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/hash.h"


/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
/**
 * DataSource string parser / maker
 *
 * @package    ADOdb
 * @author     Dario Mancuso <dario@ewide.eu>
 *
 * Variations accepted:
 *
 * type(dbsyntax)://username:password@protocol+hostspec/database?option=value
 * type://username:password@protocol+hostspec:110//usr/db_file.db
 * type://username:password@hostspec/database
 * type://username:password@hostspec
 * type://username@hostspec
 * type://hostspec/database
 * type://hostspec
 * type:///database
 * type:///database?option=value&anotheroption=anothervalue
 * type(dbsyntax)
 * type
 *
 * - type: Database backend used in PHP (i.e. mysql , odbc etc.)
 * - dbsyntax: Database used with regards to SQL syntax etc. When using ODBC as
 *   the type, set this to the DBMS type the ODBC driver is connecting to.
 *   Examples: access, db2, mssql, navision, solid, etc.
 *
 * - protocol: Communication protocol to use ( i.e. tcp, unix etc.)
 * - hostspec: Host specification (hostname[:port])
 * - database: Database to use on the DBMS server
 * - username: User name for login
 * - password: Password for login
 * - proto_opts: Maybe used with protocol
 * - option: Additional connection options in URI query string format. options
 *   get separated by &
 */
ZEPHIR_INIT_CLASS(ADOdb_DataSource) {

	ZEPHIR_REGISTER_CLASS(ADOdb, DataSource, adodb, datasource, adodb_datasource_method_entry, 0);

	zend_declare_property_null(adodb_datasource_ce, SL("dsn"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("name"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("type"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("dbsyntax"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("protocol"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("hostname"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("port"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("database"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("username"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("password"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(adodb_datasource_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_string(adodb_datasource_ce, SL("DSN_PARSE_REGEXP"), "|^(?P<type>\\w+)([\\(](?P<dbsyntax>\\w+)[\\)])?(://(((?P<username>\\w+)(:(?P<password>\\w+))?)@)?(((?P<protocol>\\w+)\\+)?(?P<hostname>\\w+)(:(?P<port>\\d+))?)?(\\/?(?P<database>[^\\s\\?]*)?)?(\\?(?P<options>\\S+))?)?$|i" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(ADOdb_DataSource, __construct) {

	zval *dsn_param = NULL;
	zval *dsn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &dsn_param);

	if (!dsn_param) {
		ZEPHIR_INIT_VAR(dsn);
		ZVAL_EMPTY_STRING(dsn);
	} else {
		zephir_get_strval(dsn, dsn_param);
	}


	if (!ZEPHIR_IS_STRING(dsn, "")) {
		zephir_call_method_p1_noret(this_ptr, "setdsn", dsn);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Parse a data source name
 *
 * @param dsn string Data Source Name to be parsed
 *
 * @return array an associative array with the following keys:
 *
 *  type    : Database backend used in PHP (mysql, odbc etc.)
 *  dbsyntax: Database used with regards to SQL syntax etc.
 *  protocol: Communication protocol to use (tcp, unix etc.)
 *  hostname: Hostname specification
 *  port    : Port
 *  database: Database to use on the DBMS server
 *  username: User name for login
 *  password: Password for login
 *
 * The format of the supplied DSN is in its fullest form:
 *
 *  type(dbsyntax)://username:password@protocol+hostspec/database
 */
PHP_METHOD(ADOdb_DataSource, parseDSN) {

	zend_class_entry *_4;
	zval *dsn_param = NULL, *p, *options = NULL, *_0, _1, *output, *_2 = NULL, *_3;
	zval *dsn = NULL, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dsn_param);

		zephir_get_strval(dsn, dsn_param);


	ZEPHIR_INIT_VAR(p);
	array_init(p);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "|^(?P<type>\\w+)([\\(](?P<dbsyntax>\\w+)[\\)])?(://(((?P<username>\\w+)(:(?P<password>\\w+))?)@)?(((?P<protocol>\\w+)\\+)?(?P<hostname>\\w+)(:(?P<port>\\d+))?)?(\\/?(?P<database>[^\\s\\?]*)?)?(\\?(?P<options>\\S+))?)?$|i", 0);
	zephir_preg_match(_0, &(_0), &_1, dsn, p, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_0)) {
		ZEPHIR_OBS_VAR(options);
		zephir_array_fetch_string(&options, p, SL("options"), PH_NOISY TSRMLS_CC);
		if (zephir_is_true(options)) {
			ZEPHIR_INIT_VAR(output);
			array_init(output);
			Z_SET_ISREF_P(output);
			zephir_call_func_p2_noret("parse_str", options, output);
			Z_UNSET_ISREF_P(output);
			ZEPHIR_CPY_WRT(options, output);
		} else {
			ZEPHIR_INIT_NVAR(options);
			array_init(options);
		}
		array_init_size(return_value, 12);
		ZEPHIR_OBS_VAR(_2);
		zephir_array_fetch_string(&_2, p, SL("type"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("type"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("dbsyntax"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("dbsyntax"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("protocol"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("protocol"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("hostname"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("hostname"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("port"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("port"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("database"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("database"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("username"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("username"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, p, SL("password"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("password"), &_2, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&return_value, SL("options"), &options, PH_COPY | PH_SEPARATE);
		RETURN_MM();
	} else {
		ZEPHIR_INIT_VAR(_3);
		_4 = zend_fetch_class(SL("InvalidArgumentException"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_3, _4);
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CONCAT_SV(_5, "Invalid DSN: ", dsn);
		zephir_call_method_p1_noret(_3, "__construct", _5);
		zephir_throw_exception(_3 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_DataSource, __toString) {


	RETURN_MEMBER(this_ptr, "dsn");

}

PHP_METHOD(ADOdb_DataSource, getDsn) {


	RETURN_MEMBER(this_ptr, "dsn");

}

PHP_METHOD(ADOdb_DataSource, getType) {


	RETURN_MEMBER(this_ptr, "type");

}

PHP_METHOD(ADOdb_DataSource, getDbsyntax) {


	RETURN_MEMBER(this_ptr, "dbsyntax");

}

PHP_METHOD(ADOdb_DataSource, getProtocol) {


	RETURN_MEMBER(this_ptr, "protocol");

}

PHP_METHOD(ADOdb_DataSource, getHostname) {


	RETURN_MEMBER(this_ptr, "hostname");

}

PHP_METHOD(ADOdb_DataSource, getPort) {


	RETURN_MEMBER(this_ptr, "port");

}

PHP_METHOD(ADOdb_DataSource, getDatabase) {


	RETURN_MEMBER(this_ptr, "database");

}

PHP_METHOD(ADOdb_DataSource, getUsername) {


	RETURN_MEMBER(this_ptr, "username");

}

PHP_METHOD(ADOdb_DataSource, getPassword) {


	RETURN_MEMBER(this_ptr, "password");

}

PHP_METHOD(ADOdb_DataSource, getOptions) {


	RETURN_MEMBER(this_ptr, "options");

}

PHP_METHOD(ADOdb_DataSource, getOption) {

	zval *name_param = NULL, *_0, *_1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

		zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	if (zephir_array_isset(_0, name)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(ADOdb_DataSource, setDsn) {

	HashTable *_2;
	HashPosition _1;
	zval *value_param = NULL, *parsed, *_0, *name = NULL, *val = NULL, **_3;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("dsn"), value TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dsn"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(parsed);
	zephir_call_self_p1(parsed, this_ptr, "parsedsn", _0);
	zephir_is_iterable(parsed, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(name, _2, _1);
		ZEPHIR_GET_HVALUE(val, _3);
		zephir_update_property_this(this_ptr, SL("name"), val TSRMLS_CC);
	}
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setType) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("type"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setDbsyntax) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("dbsyntax"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setProtocol) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("protocol"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setHostname) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("hostname"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setPort) {

	zval *value, *_0;

	zephir_fetch_params(0, 1, 0, &value);



	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, zephir_get_intval(value));
	zephir_update_property_this(this_ptr, SL("port"), _0 TSRMLS_CC);
	RETURN_THISW();

}

PHP_METHOD(ADOdb_DataSource, setDatabase) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("database"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setUsername) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("username"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setPassword) {

	zval *value_param = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

		zephir_get_strval(value, value_param);


	zephir_update_property_this(this_ptr, SL("password"), value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setOption) {

	zval *name_param = NULL, *value;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

		zephir_get_strval(name, name_param);


	zephir_update_property_array(this_ptr, SL("options"), name, value TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(ADOdb_DataSource, setOptions) {

	zval *options;
	zval *value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value);

	ZEPHIR_INIT_VAR(options);
	array_init(options);


	if ((Z_TYPE_P(value) == IS_ARRAY)) {
		Z_SET_ISREF_P(options);
		zephir_call_func_p2_noret("parse_str", value, options);
		Z_UNSET_ISREF_P(options);
		zephir_update_property_this(this_ptr, SL("options"), options TSRMLS_CC);
	} else {
		zephir_update_property_this(this_ptr, SL("options"), value TSRMLS_CC);
	}
	RETURN_THIS();

}

