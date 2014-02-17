
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_ADODB_H
#define PHP_ADODB_H 1

#include "kernel/globals.h"

#define PHP_ADODB_NAME    "adodb"
#define PHP_ADODB_VERSION "0.0.1"
#define PHP_ADODB_EXTNAME "adodb"



ZEND_BEGIN_MODULE_GLOBALS(adodb)

	/* Memory */
	zephir_memory_entry *start_memory;
	zephir_memory_entry *active_memory;

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/* Function cache */
	HashTable *function_cache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(adodb)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(adodb)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(adodb_globals_id, zend_adodb_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (adodb_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_adodb_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(adodb_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(adodb_globals)
#endif

#define zephir_globals adodb_globals
#define zend_zephir_globals zend_adodb_globals

extern zend_module_entry adodb_module_entry;
#define phpext_adodb_ptr &adodb_module_entry

#endif
