/*
 * contrib/conv_units/converter.c
 */ 

#include "converter.h"

/*
 * A complex function whose mode of operation is determined by the accepted 
 * argument 'mode' of type int. In essence, it aggregates three separate functions. 
 * This decision was made to be able to work with a static pool in the context of the function. 
 * Depending on the value of this argument, it performs the following operations:
 *
 *   -1. Creates a converter pool of the received size.
 *    0. Sets up a converter from the pool by the received index.
 *    1. Converts the received value by the converter by the received index.

 * Accepts: 
 *		+ A pointer to the instruction storage.
 * 		+ The mode of the function.
 * 		+ An argument of type int, which is perceived, depending on the mode, 
 *   	  either as the size of the created converter pool or as the index 
 *		  of the converter to work with.
 * 		+ Two c-strings containing the designation of the units of measurement received and target. 
 *		  Used only in mode 0.
 *		+ A value of type double, which is converted in mode 1.
 * 		+ A pointer to which the report on the converter setup will be placed. Used in mode 0.
 */
double 
manageConversion(INSTRUCTIONSSTORE *store, int mode, unsigned int size_or_index, char* from_units, char* to_units, double value, char** out_str)
{
	static CONVERTERSPOOL pool;
	double result; 
	
	result = 0;
	
	switch(mode)
	{
		case -1:
			if(size_or_index > 0)						
				createConvertorsPool(&pool, size_or_index);			
			break;
		case 0:
			if(configureConverter(store, &pool, from_units, to_units, size_or_index))
				(*out_str) = psprintf("The converter №%d configured: %s -> %s", size_or_index, from_units, to_units);
			else
				(*out_str) = psprintf("The converter was not configured.");
	
			break;
		case 1:
			result = convert(&pool, value, size_or_index);
	
			break;
		default:
			ereport(NOTICE, errmsg("Unknown operating mode."));
			break;		
	}	
	return result;
}


/*
 * Creates a converter pool of the received size.
 */
void 
createConvertorsPool(CONVERTERSPOOL* pool, unsigned int pool_size)
{	
	if(pool->converters != NULL)
		pfree(pool->converters);

	pool->size = pool_size;

	pool->converters = palloc(pool_size * sizeof(CONVERTER));

	for(int i = 0; i < pool_size; i++) 
	{
		pool->converters[i].description = NULL;
		pool->converters[i].func_from_si = NULL;
		pool->converters[i].func_to_si = NULL;
		pool->converters[i].coef_from_si = 0;
		pool->converters[i].coef_to_si = 0;
	}
}

/*
 * Sets up a converter from the pool by the received index.
 */
bool 
configureConverter(INSTRUCTIONSSTORE* store, CONVERTERSPOOL* pool, char* from_units, char* to_units, unsigned int converter_index)
{
	CONVERTER* converter;	

	bool is_simple_conv;

	function_converter func_from_si;
	function_converter func_to_si;

	double coef;

	if(converter_index < pool->size)
	{	
		converter = &(pool->converters[converter_index]);

		converter->coef_to_si = converter->coef_from_si = 1;

		if(findInstruction(store, from_units, &is_simple_conv, &func_to_si, &func_from_si, &coef) == false)
		{
			ereport(NOTICE, errmsg("The %s unit of measurement is unknown", from_units));
			return false;
		}
		
		if(is_simple_conv)
		{
			converter->coef_to_si = coef;
			converter->func_to_si = NULL;
		}
		else
		{	
			converter->func_to_si = func_to_si;	
		}

		if(findInstruction(store, to_units, &is_simple_conv, &func_to_si, &func_from_si, &coef) == false)
		{
			ereport(NOTICE, errmsg("The %s unit of measurement is unknown", to_units));
			return false;
		}

		if(is_simple_conv)
		{

			converter->coef_from_si = 1. / coef;
	
			converter->func_from_si = NULL;
		}
		else
		{	
			converter->func_from_si = func_from_si;	
		}
		converter->description = psprintf("Converter №%d: %s -> %s", converter_index, from_units, to_units);
	}
	else 
	{
		ereport(NOTICE, errmsg("Invalid index. The pool contains only %d converters indexed from 0.", pool->size));
		return false;
	}
	return true;
}

/*
 * Converts the received value by the converter by the received index.
 */
double 
convert(CONVERTERSPOOL* pool, double value, unsigned int converter_index)
{
	CONVERTER* converter;	
	double result;	

	if(converter_index < pool->size)
	{
		converter = &(pool->converters[converter_index]);

		if(converter->description != NULL)
		{		
			if(converter->func_to_si != NULL)
				result = converter->func_to_si(value);
			else result = value * converter->coef_to_si;		
		
			if(converter->func_from_si != NULL)
				result = converter->func_from_si(result);
			else						
				result *= converter->coef_from_si;			
		}
		else
		{
			ereport(NOTICE, errmsg("Сonverter not configured."));
			result = 0;
		}		
	}
	else 
	{	
		ereport(NOTICE, errmsg("Invalid index. The pool contains only %d converters indexed from 0.", pool->size));
		result = 0;
	}	
	return result;
}

