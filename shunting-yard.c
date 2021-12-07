#include "shunting-yard.h"
#include "symboltable.h"
#include "list.h"
#include "dict.h"
#include "stack.h"

static SymbolTable* Newtable(Tokenizer* tokenizer)
{
	SymbolTable* st = stcreate();
	
}
int syEvaluate(Tokenizer *tokenizer, SymbolTable *st, double* solution)
{
	Stack *Sop  = stackCreate();
	Stack *Sval = stackCreate();

	Token * token = tokenizerGetNextToken(tokenizer);
	TokenType tokentype;

	while( tokenGetType(token) != T_STOP )
	{
		tokentype = tokenGetType(token);
		 if(tokentype == T_NUMBER)
		 {
			double *a = tokenGetValue(token);
			push(Sval, a);
		 }
		 else if(tokentype == T_LEFTPAR)
		 {
			push(Sop, token);
		 }
		 else if(tokentype == T_SYMBOL)
		 {
		 	//tokenizerGetNextToken -> pos++
		 	TokenType tkt_symbol_aux = tokentype;
		 	token = tokenizerGetNextToken(tokenizer);

			if(tokenGetType(token) == T_LEFTPAR)
			{
				push(Sop, tkt_aux);
				push(Sop, token);
			}
			 else
			 {
				double *result = malloc(sizeof(double));
				int a = stGetVariableValue(st, tokenGetValue(token),result);
				 
				if(a)
					push(Sval, *result)
					continue;
				else{
						fprintf(stderr, "le variable \' %s \'n'a pas ete declare!\n", tokenGetValue(token));
						exit(-1);
					}

			 }
		 }
		 
		 else if(tokentype == T_OPERATOR)
		 {
			 char* symbol_op1 = malloc(sizeof(char));
			 symbol_op1 = tokenGetValue(token);
			 Token* token_top = malloc(sizeof(Token));
			 token_top = stackTop(Sop);
			 
			 while( tokenGetType(token_top) == T_OPERATOR )
			 {
				 int prec_op1 = stGetOperatorPrec(st, symbol_op1);
				 int prec_op2 = stGetOperatorPrec(st, tokenGetValue(token_top));
				 int assoc_op1 = stGetOperatorAssoc(st, symbol_op1); 
				 
				 if(prec_op1 == -1 || prec_op2 == -1 || assoc_op2 == -1)
					 exit(failure);
				 
				 if(prec_op2 > prec_op1 || (prec_op1 == prec_op2 && assoc_op1 == 0))
				 {
					 token_top = stackPop(Sop);
					 double* v1 = stackPop(Sval);
					 double* v2 = stackPop(Sval);
					 
					 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
					 double *val = malloc(sizeof(double));
					 *val = f(*v2,*v1);
					 
					 stackPush(Sval, val);
				 }
				 
				 token_top = stackTop(Sop);
			 }
			 
			 stackPush(Sop, token);
			 
			 free(symbol_op1);
			 free(token_top);
			 
		 }
		 
		 else if(tokentype == T_RIGHTPAR)
		 {
			 Token* token_top = malloc(sizeof(Token));
			 token_top = stackTop(Sop);
			 
			 while(tokenGetType(token_top) != T_LEFTPAR)
			 {
				 	 token = stackPop(Sop);
					 double* v1 = stackPop(Sval);
					 double* v2 = stackPop(Sval);
					 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token));
					 double* val = malloc(sizeof(double));
					 *val = f(*v2, *v1);
					 stackPush(Sval,val);
			 }
			 
			 Token* token_L= malloc(sizeof(Token));
			 token_L = stackPop(Sop);
			 
			 if(tokenGetType(stackTop(Sop)) == T_SYMBOL)
			 {
				 double *v = stackPop(Sval);
				 FunctionFctType f = stGetFunctionFct(st, tokenGetValue(stackTop(Sop));
				 double* val = malloc(sizeof(double));
				 *val = f(*v)
				 stackPush(Sval, val);
			 }
			 
			 free(token_top);
			 free(token_L);
		 }
		 
		 while(tokenGetType(stackTop(Sop)) == T_OPERATOR)
			 
		 {
			 Token* token_top = malloc(sizeof(Token));
			 token_top = StackPop(Sop);
			 
			 double* v1 = stackPop(Sval);
			 double* v2 = stackPop(Sval);
			 
			 FunctionFctType f = stGetFunctionFct(st, tokenGetValue(token_top));
			 double* val  = malloc(sizeof(double));
			 
			 *val = f(*v2, *v1);
			 
			 stackPush(Sval, val);
			 free(token_top);
		 }
	 
		
