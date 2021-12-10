#include "shunting-yard.h"
#include "symboltable.h"
#include "list.h"
#include "dict.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
// static SymbolTable* Newtable(Tokenizer* tokenizer)
// {
// 	SymbolTable* st = stCreate();
// 	return st;
	
// }
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
			double *a = (double*) tokenGetValue(token);
			stackPush(Sval, a);
		 }
		 else if(tokentype == T_LEFTPAR)
		 {
			stackPush(Sop, token);
		 }
		 else if(tokentype == T_SYMBOL)
		 {
		 	//tokenizerGetNextToken -> pos++
		 	//Token *tkn_symbol_aux = token;
		 	Token* token_next = tokenizerGetNextToken(tokenizer);

			if(tokenGetType(token_next) == T_LEFTPAR)
			{
				stackPush(Sop, token);
				//stackPush(Sop, token);
			}
			 else
			 {
				double *result = malloc(sizeof(double));
				int a = stGetVariableValue(st, tokenGetValue(token),result);
				 
				if(a){
							stackPush(Sval, result);
							continue;
				}
				
				else{
						    // fprintf(stderr, "le variable \' %s \'n'a pas ete declare!\n", tokenGetValue(token));
						    exit(-1);
					}

			 }
		 }
		 
		 else if(tokentype == T_OPERATOR)
		 {
			 char* symbol_op1 = malloc(sizeof(char));
			 symbol_op1 = tokenGetValue(token);
			 // Token* token_top = malloc(sizeof(Token));
			 
			 //Token* token_top = stackTop(Sop);
			 
			 while( !(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR )
			 {
				 Token* token_top = stackTop(Sop);
				 int prec_op1 = stGetOperatorPrec(st, symbol_op1);
				 int prec_op2 = stGetOperatorPrec(st, tokenGetValue(token_top));
				 int assoc_op1 = stGetOperatorAssoc(st, symbol_op1); 
				 
				 if(prec_op1 == -1 || prec_op2 == -1 || assoc_op1 == -1)
					 exit(EXIT_FAILURE);
				 
				 if(prec_op2 > prec_op1 || (prec_op1 == prec_op2 && assoc_op1 == 0))
				 {
					 token_top = stackPop(Sop);
					 
					 if(stackIsEmpty(Sval))
						 exit(EXIT_FAILURE);
					 
					 double* v1 = stackPop(Sval);
					 
					 if(stackIsEmpty(Sval));
					 exit(EXIT_FAILURE);
					 
					 double* v2 = stackPop(Sval);
					 
					 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
					 double *val = malloc(sizeof(double));
					 *val = f(*v2,*v1);
					 
					 stackPush(Sval, val);
				 }
				 
				 //token_top = stackTop(Sop);
			 }
			 
			 stackPush(Sop, token);
			 
			 free(symbol_op1);
			 
		 }
		 
		 else if(tokentype == T_RIGHTPAR)
		 {
			 // Token* token_top = malloc(sizeof(Token));
			 //Token* token_top = stackTop(Sop);
			 
			 if(stackIsEmpty(Sop))
				 exit(EXIT_FAILURE);
			 
			 while(tokenGetType(stackTop(Sop)) != T_LEFTPAR)
			 {
				     
				 	 Token* token_top = stackPop(Sop);
					 
					 if(stackIsEmpty(Sop))
						 exit(EXIT_FAILURE);
					 
					 if(stackIsEmpty(Sval))
						 exit(EXIT_FAILURE);
					 double* v1 = stackPop(Sval);
					 
					 if(stackIsEmpty(Sval))
						 exit(EXIT_FAILURE);
					 double* v2 = stackPop(Sval);
					 
					 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
					 double* val = malloc(sizeof(double));
					 *val = f(*v2, *v1);
					 stackPush(Sval,val);
			 }
			 
			 // Token* token_L= malloc(sizeof(Token));
			 Token* token_L = stackPop(Sop);
			 
			 if(!(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_SYMBOL)
			 {
				 double *v = stackPop(Sval);
				 FunctionFctType f = stGetFunctionFct(st, tokenGetValue(stackTop(Sop)));
				 double* val = malloc(sizeof(double));
				 *val = f(*v);
				 stackPush(Sval, val);
			 }
		 }
		 
		 while( !(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR)
			 
		 {
			 // Token* token_top = malloc(sizeof(Token));
			 Token* token_top = stackPop(Sop);
			 
			 double* v1 = stackPop(Sval);
			 double* v2 = stackPop(Sval);
			 
			 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
			 double* val  = malloc(sizeof(double));
			 
			 *val = f(*v2, *v1);
			 
			 stackPush(Sval, val);
		 }
	}
	
	if(stackIsEmpty(Sop))
		return 0;
	else
	{
		solution = stackPop(Sval);
		
		if(stackIsEmpty(Sval))
			return 0;
		else
			return 1
	}
}
	 
		
