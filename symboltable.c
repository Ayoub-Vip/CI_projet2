#include "symboltable.h"
#include "list.h"
#include "dict.h"
#include "stack.h"
#include "stdlib.h"
#include "stdio.h"

struct SymbolTable_t {
	Dict *S_table_dict;
	List *S_table_list;

} ;

typedef struct  {
	int prec;
	int assoc;
	double (*f)(double, double);

} Operator_STR;

typedef struct {
	double (*f)(double);
} FunctionStruct;

typedef struct {
	FunctionFctType opt;
} Function_STR;



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
	Operator_STR *newStructureOperation = malloc(sizeof(Operator_STR));
	newStructureOperation->prec = prec;
	newStructureOperation->assoc = assoc;
	newStructureOperation->f = opf;

	//insert in dictionnary
	dictInsert(st->S_table_dict, symbol, newStructureOperation);
	listAdd(st->S_table_list, newStructureOperation);
}


void stInsertFunction(SymbolTable *st, char *symbol, FunctionFctType f) {
	
	FunctionStruct* Function = malloc(sizeof(FunctionStruct));
	Function->f = f;
	dictInsert(st->S_table_dict, symbol, Function);
	listAdd(st->S_table_list, Function);
}


void stInsertVariable(SymbolTable *st, char *symbol, double val) {
	double *pt_val = malloc(sizeof(double));
	*pt_val = val;

	dictInsert(st->S_table_dict, symbol, pt_val);
	listAdd(st->S_table_list, pt_val);


}

int stContainsOperator(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol);
}


int stContainsFunction(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol);
}


int stContainsVariable(SymbolTable *st, char *symbol) {
	return dictContains(st->S_table_dict, symbol);
}


OperatorFctType stGetOperatorFct(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return (OperatorFctType) (( (Operator_STR*) dictSearch(st->S_table_dict, symbol))->f);
	else
		return 0;

}


int stGetOperatorPrec(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol)){
		Operator_STR* oppt = dictSearch(st->S_table_dict, symbol);
			return oppt->prec;
	}
	else
		return 0;

}


int stGetOperatorAssoc(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return (int)(((Operator_STR*) dictSearch(st->S_table_dict, symbol))->assoc);
	else
		return 0;

}


FunctionFctType stGetFunctionFct(SymbolTable *st, char *symbol) {

	if (stContainsOperator(st, symbol))
		return (FunctionFctType) ((FunctionStruct*) dictSearch(st->S_table_dict, symbol))->f;
	else
		fprintf(stderr,"the C prec Function was not founded");
	return 0;

}


int stGetVariableValue(SymbolTable *st, char *symbol, double* result) {

	if (stContainsVariable(st, symbol)){
		*result = (double) *((double*) dictSearch(st->S_table_dict, symbol));
		return 1;
		}
	else
		fprintf(stderr,"the C prec Function was not founded");
	return 0;

}
