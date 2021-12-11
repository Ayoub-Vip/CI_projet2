#include "shunting-yard.h"
#include "symboltable.h"
#include "tokenizer.h"
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
	List  *list = listCreate();

	Token * token = tokenizerGetNextToken(tokenizer);
	TokenType tokentype;


	while( tokenGetType(token) != T_STOP)  {

		fprintf(stderr, "while principle\n");

		 tokentype = tokenGetType(token);
		// fprintf(stderr, "tokentype:%d \n",tokentype);
		 
		 if(tokentype == T_NUMBER)
		 {
			double *a = malloc(sizeof(double));
			listAdd(list, a);
			*a =  *((double*) tokenGetValue(token));
			stackPush(Sval, a);
			fprintf(stderr, "T_NUMBER: le variable %f!\n", *((double*)stackTop(Sval)));
		 }

		 else if(tokentype == T_LEFTPAR)
		 {
			stackPush(Sop, token);

		 }

		 else if(tokentype == T_SYMBOL)
		 {
			 //tokenizerGetNextToken -> pos++
		 	Token* token_next = tokenizerGetNextToken(tokenizer);

			if(tokenGetType(token_next) == T_LEFTPAR)
			{
				stackPush(Sop, token);
				// stackPush(Sop, token_next);
			}
			else
			{
				double *result = malloc(sizeof(double));
				listAdd(list, result);
				int a = stGetVariableValue(st, tokenGetValue(token),result);

				if(a){
					stackPush(Sval, result);
					token = token_next;
					continue;
				}
				else
				{
					fprintf(stderr, "le variable s n'a pas ete declare!\n");
					exit(-1);
				}

			 }
		 }

		 else if(tokentype == T_OPERATOR)
		 {

			 char *symbol_op1 = tokenGetValue(token);
		
			 while( !(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR)
			 {
				 Token* token_top = stackTop(Sop);
				 int prec_op1 = stGetOperatorPrec(st, symbol_op1);
				 int prec_op2 = stGetOperatorPrec(st, tokenGetValue(token_top));
				 int assoc_op1 = stGetOperatorAssoc(st, symbol_op1); 

				 if (prec_op1 == -1 || prec_op2 == -1 || assoc_op1 == -1) {
					 exit(EXIT_FAILURE);
				 	 fprintf(stderr, "les precedances \' s \'n'ont pas ete declare!\n");
				 }

				 if (prec_op2 > prec_op1 || (prec_op1 == prec_op2 && assoc_op1 == 0))
				 {
				 	 if(stackIsEmpty(Sop)){
				 	 	fprintf(stderr, "le Sop n'a pas ete trouve!\n");
				 	 	exit(EXIT_FAILURE);
				 	 }

					 token_top = stackPop(Sop);

					 if(stackIsEmpty(Sval)){
					 	 exit(EXIT_FAILURE);
					 }
					 double* v1 = stackPop(Sval);

					 if(stackIsEmpty(Sval)){
					  	exit(EXIT_FAILURE);}

					 double* v2 = stackPop(Sval);

					 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));

					 double *val = malloc(sizeof(double));
					 listAdd(list, val);

					 *val = f(*v2,*v1);

					 stackPush(Sval, val);

				 }
				 else
				 	break;

				 //token_top = stackTop(Sop);
			 }

			 stackPush(Sop, token);
			 // stackPush(Sop, tokenGetValue(token));

		 }

		 else if(tokentype == T_RIGHTPAR)
		 {
			 if(stackIsEmpty(Sop)){
				 fprintf(stderr, "Sop is empty-no func\n");
			 	 exit(EXIT_FAILURE);
			 }

			 while(!stackIsEmpty(Sop) && tokenGetType(stackTop(Sop)) != T_LEFTPAR)
			 {
				 if(stackIsEmpty(Sop)) {
					 fprintf(stderr, "Sop is empty-no func\n");
					 exit(EXIT_FAILURE);
				 }
				 Token* token_top = stackPop(Sop);

				 if(stackIsEmpty(Sval)){
					 fprintf(stderr, "Sval is empty-no var\n");
					 exit(EXIT_FAILURE);
				 }
				 double* v1 = stackPop(Sval);
				 
				 if(stackIsEmpty(Sval)){
					 fprintf(stderr, "Sval is empty-no var\n");
					 exit(EXIT_FAILURE);
				 }
				 double* v2 = stackPop(Sval);

				OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
				double* val = malloc(sizeof(double));
				listAdd(list, val);
				*val = f(*v2, *v1);
				stackPush(Sval,val);

			}

			 // Token* token_L= malloc(sizeof(Token));
			 if (!stackIsEmpty(Sop) && tokenGetType(stackTop(Sop)) == T_LEFTPAR){
			 			 	Token* token_L = stackPop(Sop);
			 			 	printf("T_LEFTPAR est retire\n");
			 }else{
			 	printf("T_LEFTPAR est retire\n");
			 	exit(EXIT_FAILURE);
			 }

			 if(!stackIsEmpty(Sop) && tokenGetType(stackTop(Sop)) == T_SYMBOL)
			 {
				 double *v = stackPop(Sval);
				 FunctionFctType f = stGetFunctionFct(st, tokenGetValue(stackTop(Sop)));
				 double* val = malloc(sizeof(double));
				 listAdd(list, val);
				 *val = f(*v);
				 stackPush(Sval, val);
			 }
		 }


		 
		 token = tokenizerGetNextToken(tokenizer);
	}
	while( !(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR)
		 {
			 Token* token_top = stackPop(Sop);

			 if(stackIsEmpty(Sval)){
			 	fprintf(stderr, "sop empty for V1\n");
				 exit(EXIT_FAILURE);}
			 double* v1 = stackPop(Sval);

			 if(stackIsEmpty(Sval)){
				 fprintf(stderr, "sop empty for V2\n");
				 exit(EXIT_FAILURE);
			 }
			 double* v2 = stackPop(Sval);

			 OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
			 double* val  = malloc(sizeof(double));
			 listAdd(list, val);

			 *val = f(*v2, *v1);

			 stackPush(Sval, val);

		 }
	// listFree(list);

	// if(!stackIsEmpty(Sop))
	// 	return 0;
	// else
	// {
		if(stackIsEmpty(Sval))
			return 0;
		else{
				*solution = (double) *((double*)stackPop(Sval));
				return 1;
			}

	// }


}
