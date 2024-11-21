/******************************************************************************
  contrib/conv_units/converter.h
  
  The file is the header of the main logic part of the extension. 
  It defines the structure of the physical quantity converter, 
  the pool of these converters, and also declares functions for working with them.
******************************************************************************/
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "instructions_store.h"
#include "converter.h"

typedef struct CONVERTER
{
	char* description;
	
	function_converter func_from_si;
	function_converter func_to_si;
	
	double coef_from_si;
	double coef_to_si;

}CONVERTER;

typedef struct CONVERTERSPOOL
{
	unsigned int size;

	CONVERTER* converters;

}CONVERTERSPOOL;

/*
 * A complex function whose mode of operation is determined by the accepted 
 * argument 'mode' of type int.
 * Depending on the value of this argument, it performs the following operations:
 *
 *   -1. Creates a converter pool of the received size.
 *    0. Sets up a converter from the pool by the received index.
 *    1. Converts the received value by the converter by the received index.
 */
double manageConversion(INSTRUCTIONSSTORE* store, int mode, unsigned int size_or_index, char* from_units, char* to_units, double value, char** out_str);

/*
 * Creates a converter pool of the received size.
 */
void createConvertorsPool(CONVERTERSPOOL* pool, unsigned int pool_size);

/*
 * Sets up a converter from the pool by the received index.
 */
bool configureConverter(INSTRUCTIONSSTORE* store, CONVERTERSPOOL* pool, char* from_units, char* to_units, unsigned int converter_index);

/*
 * Converts the received value by the converter by the received index.
 */
double convert(CONVERTERSPOOL* pool, double value, unsigned int converter_index);

#endif
