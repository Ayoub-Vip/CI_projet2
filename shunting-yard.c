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
	while()
	{
		token = Token *tokenizerGetNextToken(Tokenizer *tokenizer) ;
		tokentype = tokenGetType(Token *token);
		
		 if(tokentype == T_NUMBER)
		 {
			 double *a = tokenGetValue(Token *token);
			 push(sval, a);
		 }
		 
		 else if(tokentype == LEFTPAR)
		 {
			 push(sop, token);
		 }
		 
		 else if(tokentype == T_SYMBOL)
		 {
			 if( gettype(tokenizerGetNextToken(tokenizer)) == LEFTPAR)
			 {
				 push(sop, token);
			 }
			 else
			 {
				 double *result = malloc(sizeof(double));
				 int a = stGetVariableValue(st, ...,result);
				 
				 if(a==1)
					 push(Sval, *result)
				 else
					 fprintf(stderr, "pas de variable");
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
			 
					 
					 
			 
			 
			
			 
		
			 
			 
			 
