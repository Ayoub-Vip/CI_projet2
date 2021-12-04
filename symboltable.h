#ifndef ST_H
#define ST_H


typedef struct SymbolTable_t SymbolTable;

// Type of the C functions associated to 'functions', i.e. takes one double
// as argument and returns a double.
typedef double (* FunctionFctType)(double);

// Type of the C functions associated to 'operators', i.e. takes two doubles
// as argument and returns a double.
typedef double (* OperatorFctType)(double, double);


/* Create an empty symbol table.
 *
 * RETURNS: the created symbol table.
 */
SymbolTable *stCreate(void);

/* Deallocate the memory occupied by a symbol table as well as all the symbols
 * contained in it.
 *
 * PARAMETERS:
 * - `st`: the symbol table
 */
void stFree(SymbolTable *st);


/* Add a new operator in a symbol table.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the operator.
 * - `prec`: the precedence of the operator.
 * - `assoc`: the associativity of the operator (0 for left, 1 for right).
 * - `opf`: the C function that do the operation associated to the operator.
 */
void stInsertOperator(SymbolTable *st, char *symbol, int prec, int assoc, OperatorFctType opf);

/* Add a new function in a symbol table.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the function.
 * - `f`: the C function that do the operation associated to the function.
 */
void stInsertFunction(SymbolTable *st, char *symbol, FunctionFctType f);

/* Add a new variable in a symbol table.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the variable.
 * - `val`: the value of the variable.
 */
void stInsertVariable(SymbolTable *st, char *symbol, double val);


/* Check if an operator is contained in a symbol table.
*
* PARAMETERS:
* - `st`: the symbol table.
* - `symbol`: the symbol associated to the operator.
*
* RETURNS: 1 if the operator is in the symbol table, 0 otherwise.
*/
int stContainsOperator(SymbolTable *st, char *symbol);

/* Check if a function is contained in a symbol table.
*
* PARAMETERS:
* - `st`: the symbol table.
* - `symbol`: the symbol associated to the function.
*
* RETURNS: 1 if the function is in the symbol table, 0 otherwise.
*/
int stContainsFunction(SymbolTable *st, char *symbol);

/* Check if a variable is contained in a symbol table.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the variable.
 *
 * RETURNS: 1 if the variable is in the symbol table, 0 otherwise.
 */
int stContainsVariable(SymbolTable *st, char *symbol);


/* Get a pointer to the function (of type (double,double)->double)
 *  associated to an operator.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the operator.
 *
 * RETURNS: a pointer to the function. The behavior of the function
 * is undetermined if the operator is not found in the symbol table.
 * The user is supposed to check that the operator belongs to the table
 * with stContainsOperator before calling this function.
 */
OperatorFctType stGetOperatorFct(SymbolTable *st, char *symbol);

/* Get the precedence of an operator.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the operator.
 *
 * RETURNS: the precedence of the operator if it was found in the symbol table,
 * -1 otherwise.
 */
int stGetOperatorPrec(SymbolTable *st, char *symbol);

/* Get the associativity of an operator.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the operator.
 *
 * RETURNS: the associativity of the operator if it was found in the symbol table,
 * -1 otherwise.
 */
int stGetOperatorAssoc(SymbolTable *st, char *symbol);


/* Get a pointer to the function (of type double->double) associated to a function.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the function.
 *
 * RETURNS: a pointer to the function. The behavior of the function
 * is undetermined if the function is not found in the symbol table.
 * The user is supposed to check that the function belongs to the table
 * with stContainsFunction before calling this function.

 */
FunctionFctType stGetFunctionFct(SymbolTable *st, char *symbol);


/* Get the value of a variable.
 *
 * PARAMETERS:
 * - `st`: the symbol table.
 * - `symbol`: the symbol associated to the variable.
 * - `result`: a pointer to a double where the variable's value will be stored.
 *             if the variable is not in the table, the double will be unchanged.
 *
 * RETURNS: 1 if the variable is found in the table, 0 otherwise.
 */
int stGetVariableValue(SymbolTable *st, char *symbol, double* result);

#endif
