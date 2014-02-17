
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Statement) {

	ZEPHIR_REGISTER_INTERFACE(ADOdb, Statement, adodb, statement, adodb_statement_method_entry);


	return SUCCESS;

}

ZEPHIR_DOC_METHOD(ADOdb_Statement, errorCode);

ZEPHIR_DOC_METHOD(ADOdb_Statement, errorInfo);

ZEPHIR_DOC_METHOD(ADOdb_Statement, execute);

ZEPHIR_DOC_METHOD(ADOdb_Statement, columnCount);

ZEPHIR_DOC_METHOD(ADOdb_Statement, rowCount);

ZEPHIR_DOC_METHOD(ADOdb_Statement, canSeek);

ZEPHIR_DOC_METHOD(ADOdb_Statement, fetch);

ZEPHIR_DOC_METHOD(ADOdb_Statement, fetchAll);

ZEPHIR_DOC_METHOD(ADOdb_Statement, fetchColumn);

ZEPHIR_DOC_METHOD(ADOdb_Statement, getColumnMeta);

ZEPHIR_DOC_METHOD(ADOdb_Statement, close);

ZEPHIR_DOC_METHOD(ADOdb_Statement, timeCreated);

ZEPHIR_DOC_METHOD(ADOdb_Statement, setFetchMode);

ZEPHIR_DOC_METHOD(ADOdb_Statement, dump);

