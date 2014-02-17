
extern zend_class_entry *adodb_datasource_ce;

ZEPHIR_INIT_CLASS(ADOdb_DataSource);

PHP_METHOD(ADOdb_DataSource, __construct);
PHP_METHOD(ADOdb_DataSource, parseDSN);
PHP_METHOD(ADOdb_DataSource, __toString);
PHP_METHOD(ADOdb_DataSource, getDsn);
PHP_METHOD(ADOdb_DataSource, getType);
PHP_METHOD(ADOdb_DataSource, getDbsyntax);
PHP_METHOD(ADOdb_DataSource, getProtocol);
PHP_METHOD(ADOdb_DataSource, getHostname);
PHP_METHOD(ADOdb_DataSource, getPort);
PHP_METHOD(ADOdb_DataSource, getDatabase);
PHP_METHOD(ADOdb_DataSource, getUsername);
PHP_METHOD(ADOdb_DataSource, getPassword);
PHP_METHOD(ADOdb_DataSource, getOptions);
PHP_METHOD(ADOdb_DataSource, getOption);
PHP_METHOD(ADOdb_DataSource, setDsn);
PHP_METHOD(ADOdb_DataSource, setType);
PHP_METHOD(ADOdb_DataSource, setDbsyntax);
PHP_METHOD(ADOdb_DataSource, setProtocol);
PHP_METHOD(ADOdb_DataSource, setHostname);
PHP_METHOD(ADOdb_DataSource, setPort);
PHP_METHOD(ADOdb_DataSource, setDatabase);
PHP_METHOD(ADOdb_DataSource, setUsername);
PHP_METHOD(ADOdb_DataSource, setPassword);
PHP_METHOD(ADOdb_DataSource, setOption);
PHP_METHOD(ADOdb_DataSource, setOptions);

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource___construct, 0, 0, 0)
  ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_parsedsn, 0, 0, 1)
  ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_getoption, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setdsn, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_settype, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setdbsyntax, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setprotocol, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_sethostname, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setport, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setdatabase, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setusername, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setpassword, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setoption, 0, 0, 2)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_adodb_datasource_setoptions, 0, 0, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(adodb_datasource_method_entry) {
	PHP_ME(ADOdb_DataSource, __construct, arginfo_adodb_datasource___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(ADOdb_DataSource, parseDSN, arginfo_adodb_datasource_parsedsn, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(ADOdb_DataSource, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getDsn, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getDbsyntax, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getProtocol, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getHostname, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getPort, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getDatabase, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getUsername, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getPassword, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getOptions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, getOption, arginfo_adodb_datasource_getoption, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setDsn, arginfo_adodb_datasource_setdsn, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setType, arginfo_adodb_datasource_settype, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setDbsyntax, arginfo_adodb_datasource_setdbsyntax, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setProtocol, arginfo_adodb_datasource_setprotocol, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setHostname, arginfo_adodb_datasource_sethostname, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setPort, arginfo_adodb_datasource_setport, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setDatabase, arginfo_adodb_datasource_setdatabase, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setUsername, arginfo_adodb_datasource_setusername, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setPassword, arginfo_adodb_datasource_setpassword, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setOption, arginfo_adodb_datasource_setoption, ZEND_ACC_PUBLIC)
	PHP_ME(ADOdb_DataSource, setOptions, arginfo_adodb_datasource_setoptions, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
