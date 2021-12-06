// #include <stdio.h>
// #include <math.h>

#include "symboltable.h"
#include "list.h"
#include "dict.h"
#include "stack.h"

{
	Dict *S_table_dict;
	List *S_table_list;

} SymbolTable_t;

{
	int prec;
	bool assoc;
	OperatorFctType opf;

} Operator_STR;
// {
// 	FunctionFctType;
// }Function_STR;

SymbolTable *stCreate(void){

	SymbolTable * ST = malloc(sizeof(SymbolTable));
	ST->S_table_dict = dictCreate(500);
	ST->S_table_list = listCreate();

	return ST;

}

// void dictFree(Dict *d);
void stFree(SymbolTable *st) {
	// Node *cur = l->first;
	// while (cur) {
	// 	Node *next = cur->next;
	// 	free(*(cur->data))
	// 	cur = next;
	// }
	dictFree(st->S_table_dict);
	listFree(st->S_table_list);
	free(st);

}

void stInsertOperator(SymbolTable *st, char *symbol, int prec, int assoc, OperatorFctType opf) {
	//create structure
	Operator_STR* newStructureOperation = malloc(sizeof(Operator_STR));
	newStructureOperation->prec = prec;
	newStructureOperation->assoc = assoc;

	//insert in dictionnary
	dictInsert(st->S_table_dict, symbol, newStructureOperation);
	listAdd(st->S_table_list, newStructureOperation);
}


void stInsertFunction(SymbolTable *st, char *symbol, FunctionFctType f) {
	dictInsert(st->S_table_dict, symbol, f);
}


void stInsertVariable(SymbolTable *st, char *symbol, double val) {
	double *pt_val = malloc(sizeof(double));
	pt_val = val;

	dictInsert(st->S_table_dict, symbol, pt_val);
	listAdd(st->S_table_list, pt_val);


}

int stContainsOperator(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol)
}


int stContainsFunction(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol)
}


int stContainsVariable(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol)
}


OperatorFctType stGetOperatorFct(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return dictContains(st, symbol)->opf;
	else
		return NULL;

}


int stGetOperatorPrec(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return dictContains(st, symbol)->prec;
	else
		return NULL;

}


int stGetOperatorAssoc(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return dictContains(st, symbol)->assoc;
	else
		return NULL;

}


FunctionFctType stGetFunctionFct(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return dictContains(st, symbol);
	else
		fprintf(stderr,'the C prec Function was not founded');
	return NULL;

}


int stGetVariableValue(SymbolTable *st, char *symbol, double* result) {

	if (stContainsOperator(st, symbol)){
		result = dictContains(st, symbol);
		return 1;
		}
	else
		fprintf(stderr,'the C prec Function was not founded');
	return NULL;

}

