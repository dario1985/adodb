
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */
ZEPHIR_INIT_CLASS(ADOdb_Driver_Cache) {

	ZEPHIR_REGISTER_INTERFACE(ADOdb\\Driver, Cache, adodb, driver_cache, adodb_driver_cache_method_entry);


	return SUCCESS;

}

ZEPHIR_DOC_METHOD(ADOdb_Driver_Cache, read);

ZEPHIR_DOC_METHOD(ADOdb_Driver_Cache, write);

ZEPHIR_DOC_METHOD(ADOdb_Driver_Cache, flush);

ZEPHIR_DOC_METHOD(ADOdb_Driver_Cache, flushAll);

