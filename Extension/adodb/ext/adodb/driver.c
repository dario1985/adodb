
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
* Data Object Interface
*/
ZEPHIR_INIT_CLASS(ADOdb_Driver) {

	ZEPHIR_REGISTER_INTERFACE(ADOdb, Driver, adodb, driver, adodb_driver_method_entry);


	return SUCCESS;

}

ZEPHIR_DOC_METHOD(ADOdb_Driver, beginTransaction);

ZEPHIR_DOC_METHOD(ADOdb_Driver, commit);

ZEPHIR_DOC_METHOD(ADOdb_Driver, errorCode);

ZEPHIR_DOC_METHOD(ADOdb_Driver, errorInfo);

ZEPHIR_DOC_METHOD(ADOdb_Driver, execute);

ZEPHIR_DOC_METHOD(ADOdb_Driver, query);

ZEPHIR_DOC_METHOD(ADOdb_Driver, inTransaction);

ZEPHIR_DOC_METHOD(ADOdb_Driver, getLastInsertId);

ZEPHIR_DOC_METHOD(ADOdb_Driver, rollBack);

