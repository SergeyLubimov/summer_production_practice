/******************************************************************************
  contrib/conv_units/instructions_store.h
  
  The file is the header of the main logic part of the extension. 
  It defines the storage of instructions for translating physical units 
  and declares functions for working with them.
******************************************************************************/

#ifndef __INSTRUCTIONS_STORE_H__
#define __INSTRUCTIONS_STORE_H__

#include "postgres.h"

#include "converter_functions.h"
#include "conv_units_configuration.h"

#include <string.h>

/*
 * The storage in this implementation is a structure storing a list of lists. 
 * Each SI unit added to the extension corresponds to a node of the SILIST type, 
 * which is stored as a singly linked list.

 * The instruction stores the conversion factor of a physical quantity into 
 * the corresponding SI unit. Or, in the case of a specific translation, 
 * a pointer to functions that perform direct and reverse conversion.

 * Instructions related to a particular SI unit are stored as a list 
 * in the corresponding SILIST.
 */

typedef struct INSTRUCTIONNODE;
typedef struct SILIST;

typedef struct INSTRUCTIONNODE
{
	bool is_node_used;

	bool is_simple_conv;

	char designation[MAX_DESIGNATION_LENGTH + 1];	
	
	function_converter func_to_si, func_from_si;
	double coef;	

	struct INSTRUCTIONNODE* next_node;

}INSTRUCTIONNODE;

typedef struct SILIST
{
	char designation[MAX_DESIGNATION_LENGTH + 1];

	int total_nodes;
	int used_nodes;

	INSTRUCTIONNODE* head;
	struct SILIST* next_node;

}SILIST;

typedef struct INSTRUCTIONSSTORE
{
	unsigned int si_units_count;
	unsigned int insturtions_count;

	struct SILIST* head;

}INSTRUCTIONSSTORE;

extern void initStore(INSTRUCTIONSSTORE** store);

extern void add_to_store(INSTRUCTIONSSTORE* store, char* designation);

extern void add_to_silist_with_coef(SILIST* silist, char* designation, double coef);

extern void add_to_silist_with_func(SILIST* silist, char* designation, function_converter func_to_si, function_converter func_from_si);

extern bool checkNode(INSTRUCTIONNODE* node, char* designation, bool* is_simple_conv, function_converter* func_to_si, function_converter* func_from_si, double* coef);

extern bool checkSIList(SILIST* silist, char* designation, bool* is_simple_conv,  function_converter* func_to_si, function_converter* func_from_si, double *coef);

extern bool findInstruction(INSTRUCTIONSSTORE* store, char* designation, bool* is_simple_conv, function_converter* func_to_si, function_converter* func_from_si, double* coef);

#endif
