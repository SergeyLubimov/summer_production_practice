/******************************************************************************
  contrib/conv_units/conv_units.c
  
  This file contains functions that can be bound to the Postgres backend and 
  called by the backend during query processing. The functions provided are 
  wrappers for functions implementing the extension logic, 
  which are defined in other files.
******************************************************************************/

#include "postgres.h"

#include "instructions_store.h"
#include "converter.h"
#include "conv_units_configuration.h"
#include "script_elements.h"
#include "inital_unit_set_script.h"

#include "fmgr.h"
#include "utils/builtins.h"

#include <string.h>
#include <stdio.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(init_conv_units);
PG_FUNCTION_INFO_V1(create_convertors_pool);
PG_FUNCTION_INFO_V1(configure_converter);
PG_FUNCTION_INFO_V1(convert_unit);

//A pointer for initialization and subsequent work with the instruction store.
static INSTRUCTIONSSTORE* store;

/*
 * A function that creates a pool of converters.
 *  
 *  * Accepts the required pool size of type integer. 
 *  * Returns a flag indicating whether the operation was successful.
 */
Datum
create_convertors_pool(PG_FUNCTION_ARGS)
{
		char *str_buff;
		int pool_size;
		bool result;
		
		pool_size = PG_GETARG_INT32(0);
		
		if(pool_size > 0)
		{			
			manageConversion(store, -1, pool_size, NULL, NULL, 0, &str_buff);
			result = true;
		}
		else
		{	
			ereport(NOTICE, errmsg("You can create only one or more converters."));
			result = false;
		}		
		PG_RETURN_BOOL(result);
}

/*
 * The function sets up the converter corresponding to the index.
 *
 *  * Accepts two text strings. The first contains the designation 
 *    of the unit of measurement of the converted value, 
 *	  the second the designation of the target unit of measurement.
 *
 *  * Returns a text string-report on the completed operation.
 */
Datum
configure_converter(PG_FUNCTION_ARGS)
{
	char *from_units, *to_units, *result;
	int converter_index;	

	from_units = text_to_cstring(PG_GETARG_TEXT_P_COPY(0));
	to_units = text_to_cstring(PG_GETARG_TEXT_P_COPY(1));	
		
	converter_index = PG_GETARG_INT32(2);
		
	manageConversion(store, 0, converter_index, from_units, to_units, 0, &result);
	
	PG_RETURN_TEXT_P(cstring_to_text(result));	
}

/*
 * Converts the given value using the converter corresponding to the given index.
 *
 *  * Accepts the double value to be converted and the index of the converter 
 *    that should perform the conversion.
 *
 *  * Returns the converted double value.
 */
Datum 
convert_unit(PG_FUNCTION_ARGS)
{
	double value, result;
	int converter_index;
	char *str_buff;
	
	value = PG_GETARG_FLOAT8(0);
	converter_index = PG_GETARG_INT32(1);
	
	result = manageConversion(store, 1, converter_index, NULL, NULL, value, &str_buff);	
	
	PG_RETURN_FLOAT8(result);	
}

/*
 * Function that initializes the extension structure. 
 * Runs when the extension is created. No user call is required. 
 * Does not accept or return arguments.
 */
Datum 
init_conv_units(PG_FUNCTION_ARGS)
{
	initStore(&store);	
	
	INITIAL_UNIT_SET_SCRIPT	
	
	PG_RETURN_VOID();
}










