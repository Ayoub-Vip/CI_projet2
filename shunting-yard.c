#include "shunting-yard.h"
#include "symboltable.h"
#include "tokenizer.h"
#include "list.h"
#include "dict.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int syEvaluate(Tokenizer *tokenizer, SymbolTable *st, double *solution)
{
    Stack * Sop  = stackCreate();
    Stack * Sval = stackCreate();
    List * list  = listCreate();

    Token *token = tokenizerGetNextToken(tokenizer);
    TokenType tokentype;

    while (tokenGetType(token) != T_STOP) {

        tokentype = tokenGetType(token);

        if (tokentype == T_NUMBER) {

            double * a = malloc(sizeof(double));
            listAdd(list, a);
            * a = * ((double * ) tokenGetValue(token));
            stackPush(Sval, a);
        }

        else if (tokentype == T_LEFTPAR) {

            stackPush(Sop, token);
        }

        else if (tokentype == T_SYMBOL) {

            Token * token_next = tokenizerGetNextToken(tokenizer);

            if (tokenGetType(token_next) == T_LEFTPAR) {
                stackPush(Sop, token);
                stackPush(Sop, token_next);
            }
            else {

                double * result = malloc(sizeof(double));
                listAdd(list, result);
                int a = stGetVariableValue(st, tokenGetValue(token), result);

                if (a) {
                    stackPush(Sval, result);
                    token = token_next;
                    continue;
                }

                else {

                    fprintf(stderr,"la valeur de variable \'%s\' n'a pas ete trouvée!\n", (char*)tokenGetValue(token));
                    exit(-1);
                }

            }
        }

        else if (tokentype == T_OPERATOR) {

            char * symbol_op1 = tokenGetValue(token);

            while (!(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR) 
            {

                Token * token_top = stackTop(Sop);
                int prec_op1  = stGetOperatorPrec(st, symbol_op1);
                int prec_op2  = stGetOperatorPrec(st, tokenGetValue(token_top));
                int assoc_op1 = stGetOperatorAssoc(st, symbol_op1);

                if (prec_op1 == -1 || prec_op2 == -1 || assoc_op1 == -1) {
                    fprintf(stderr, "les opérateurs entrés n'existent pas!\n");
                    exit(EXIT_FAILURE);
                }

                if (prec_op2 > prec_op1 || (prec_op1 == prec_op2 && assoc_op1 == 0)) {

                    token_top = stackPop(Sop);


                    if (stackIsEmpty(Sval)) {
                        fprintf(stderr, "il manque une valeur pour faire l'opération!\n");
                        exit(EXIT_FAILURE);
                    }
                    double * v1 = stackPop(Sval);


                    if (stackIsEmpty(Sval)) {
                        fprintf(stderr, "il manque une valeur pour faire l'opération !\n");
                        exit(EXIT_FAILURE);
                    }
                    double * v2 = stackPop(Sval);

                    OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));

                    double * val = malloc(sizeof(double));

                    *val = f(*v2, *v1);

                    stackPush(Sval, val);
                    listAdd(list, val);

                } else
                    break;

            }

            stackPush(Sop, token);

        }

        else if (tokentype == T_RIGHTPAR) {

            if (stackIsEmpty(Sop)) {
                fprintf(stderr, "Une parethese est ferme sans avoir ete ouvetre\n");
                exit(EXIT_FAILURE);
            }

            while (tokenGetType(stackTop(Sop)) != T_LEFTPAR)
            {
				
                Token * token_top = stackPop(Sop);
				
		if (stackIsEmpty(Sop)) {
                    fprintf(stderr, "une parenthese est fermée sans avoir été ouverte\n");
                    exit(EXIT_FAILURE);
                }


                if (stackIsEmpty(Sval)) {
                    fprintf(stderr, "il manque une valeur pour faire l'opération\n");
                    exit(EXIT_FAILURE);
                }
                double * v1 = stackPop(Sval);


                if (stackIsEmpty(Sval)) {
                    fprintf(stderr, "il manque une valeur pour faire l'opération\n");
                    exit(EXIT_FAILURE);
                }
                double * v2 = stackPop(Sval);

                OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
                double * val = malloc(sizeof(double));
                listAdd(list, val);
                * val = f( * v2, * v1);
                stackPush(Sval, val);

            }

            stackPop(Sop);

            if (!stackIsEmpty(Sop) && tokenGetType(stackTop(Sop)) == T_SYMBOL) {
                double * v = stackPop(Sval);
                FunctionFctType f = stGetFunctionFct(st, tokenGetValue(stackPop(Sop)));
                double * val = malloc(sizeof(double));
                * val = f( * v);

                stackPush(Sval, val);
                listAdd(list, val);

            }
        }

        token = tokenizerGetNextToken(tokenizer);
    }

    while (!(stackIsEmpty(Sop)) && tokenGetType(stackTop(Sop)) == T_OPERATOR)
    {


        Token * token_top = stackPop(Sop);

        if (stackIsEmpty(Sval)) {
            fprintf(stderr, "il manque une valeur pour faire l'opération\n");
            exit(EXIT_FAILURE);
        }
        double * v1 = stackPop(Sval);

        if (stackIsEmpty(Sval)) {
            fprintf(stderr, "il manque une valaur pour faire l'opération\n");
            exit(EXIT_FAILURE);
        }

        double * v2 = stackPop(Sval);

        OperatorFctType f = stGetOperatorFct(st, tokenGetValue(token_top));
        double * val = malloc(sizeof(double));

        *val = f(*v2, *v1);

        stackPush(Sval, val);
        listAdd(list, val);

    }


    if (!stackIsEmpty(Sop)) {
            fprintf(stderr, "L'expression nest pas correcte: verifiez s'il manque une parenthese ...\n");
            exit(EXIT_FAILURE);
        }

    if (stackIsEmpty(Sval))
        return 0;
    else {
        *solution = (double) *((double *) stackPop(Sval));
         listFree(list);
		 
        if (!stackIsEmpty(Sval))
            return 0;
        return 1;
     }

}
