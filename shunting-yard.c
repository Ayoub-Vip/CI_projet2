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
			 while( ...)
			 {
				 if(p1<p2 || (p1==p2 && assp1 == 0))
				 {
					 symbol = pop(sop);
					 v1 = pop(sval);
					 v2 = pop(sval);
					 f = stGetOperatorFct(SymbolTable *st, char *symbol)
					 
					 push(sval, f(v2,v1));
				 }
				 op1 = pop(sop)
			 }
		 }
		 
		 else if(tokentype == T_RIGHTPAR)
		 {
			 while(tokentype != T_LEFTPAR)
			 {
				 	 symbol = pop(sop);
					 v1 = pop(sval);
					 v2 = pop(sval);
					 f = stGetOperatorFct(SymbolTable *st, char *symbol)
					 push(sval, f(v2, v1));
			 }
			 
			 op = pop(sop);
			 
			 if(tokenGetType(top(sop)) == SYMBOL)
			 {
				 double v = pop(sval);
				 f = stGetFunctionFct(st, tokenGetValue(top(sop)) ;
				 push(sval, f(v));
			 }
		 }
			 
					 
					 
			 
			 
			
			 
		
			 
			 
			 
