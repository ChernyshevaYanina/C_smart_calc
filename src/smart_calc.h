#ifndef SMART_CALC_H
#define SMART_CALC_H

#define MAX_SIZE 255

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum priority {
  NUM = 1,
  OP_BR = 2,
  ADD = 3,
  MUL = 4,
  POW = 5,
  FUNC = 6,
  CL_BR = 7
};

typedef struct stackDouble {
  double number;
  struct stackDouble *next;
} stackD;

typedef struct createToken {
  int precedency;
  char *ptr;
} token;

typedef struct createList {
  token token_list[MAX_SIZE];
  int count_token;
} list;

stackD *initStakDouble(const double *value);
void pushDouble(stackD **stack, double *value);
double popDouble(stackD **stack);
void pushList(list *stack_list, token stack_token);
token popList(list *stack_list);
char serchFuncs(char *str);
void makeList(char *str, list *infix);
void reversePolishNotation(list *infix, list *polish);
double isOperation(char op, double operand1, double operand2);
double isFunc(char *op, double operand);
double calc(list *polish, double *result);
double toQt(const char *str, double *answer);

#endif  // SMART_CALC_H
