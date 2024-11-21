/*
 * contrib/conv_units/instructions_store_dynamic.c
 */

#if EXTENSION_BUILD_MODE == 0

#include "instructions_store.h"

void initStore(INSTRUCTIONSSTORE** store)
{	
	(*store) = palloc(sizeof(INSTRUCTIONSSTORE));	
	
	(*store)->si_units_count = MAX_SI_UNITS;
	(*store)->insturtions_count = MAX_INSTRUCTIONS_FOR_SI_UNIT;
	(*store)->head = NULL;	
}

void add_to_store(INSTRUCTIONSSTORE* store, char* designation)
{	
	SILIST* head_copy = store->head;	

	store->head = palloc(sizeof(SILIST));

	strcpy(store->head->designation, designation);

	store->head->total_nodes = 0;
	store->head->used_nodes = 0;

	store->head->next_node = head_copy;
	store->head->head = NULL;	
}

void add_to_silist_with_coef(SILIST* silist, char* designation, double coef)
{	
	INSTRUCTIONNODE* head_copy = silist->head;
	
	silist->head = palloc(sizeof(INSTRUCTIONNODE));

	strcpy(silist->head->designation, designation);

	silist->head->is_node_used = true;
	silist->head->is_simple_conv = true;

	silist->head->coef = coef;
	silist->head->func_to_si = NULL;
	silist->head->func_from_si = NULL;

	silist->head->next_node = head_copy;
}

void add_to_silist_with_func(SILIST* silist, char* designation, function_converter func_to_si, function_converter func_from_si)
{	
	INSTRUCTIONNODE* head_copy = silist->head;

	silist->head = palloc(sizeof(INSTRUCTIONNODE));
	
	strcpy(silist->head->designation, designation);

	silist->head->is_node_used = true;
	silist->head->is_simple_conv = false;

	silist->head->coef = 0;
	silist->head->func_to_si = func_to_si;
	silist->head->func_from_si = func_from_si;

	silist->head->next_node = head_copy;
}

bool checkNode(INSTRUCTIONNODE* node, char* designation, bool* is_simple_conv, function_converter* func_to_si, function_converter* func_from_si, double* coef)
{
	if(node == NULL)
		return  false;
	
	if(strcmp(node->designation, designation) == 0)
	{
		*is_simple_conv = node->is_simple_conv;	
		*coef = node->coef;	
		*func_to_si = node->func_to_si;	
		*func_from_si = node->func_from_si;
		return true;
	}
	return checkNode(node->next_node, designation, is_simple_conv, func_to_si, func_from_si, coef);	
}

bool checkSIList(SILIST* silist, char* designation, bool* is_simple_conv,  function_converter* func_to_si, function_converter* func_from_si, double *coef)
{	
	if(silist == NULL)
		return false;

	if(strcmp(silist->designation, designation) == 0)
	{
		*is_simple_conv = true;
		*coef = 1;
		*func_to_si = NULL;
		*func_from_si = NULL;
		return true;
	}

	if(checkNode(silist->head, designation, is_simple_conv, func_to_si, func_from_si, coef))
		return true;

	return checkSIList(silist->next_node, designation, is_simple_conv, func_to_si, func_from_si, coef);
}

bool findInstruction(INSTRUCTIONSSTORE* store, char* designation, bool* is_simple_conv, function_converter* func_to_si, function_converter* func_from_si, double* coef)
{
	return checkSIList(store->head, designation, is_simple_conv, func_to_si, func_from_si, coef);
}

#endif
