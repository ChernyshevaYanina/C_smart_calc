#include "smart_calc.h"

stackD *initStakDouble(const double *value) {
  stackD *tmp = (stackD *)malloc(sizeof(stackD));
  tmp->next = NULL;
  tmp->number = *value;
  return tmp;
}

void pushDouble(stackD **stack, double *value) {
  stackD *tmp = initStakDouble(value);
  tmp->next = *stack;
  *stack = tmp;
}

double popDouble(stackD **stack) {
  double number = NAN;
  if (*stack) {
    stackD *tmp = *stack;
    *stack = tmp->next;
    number = tmp->number;
    free(tmp);
  }
  return number;
}

void pushList(list *stack_list, token stack_token) {
  stack_list->count_token++;
  stack_list->token_list[stack_list->count_token] = stack_token;
}
token popList(list *stack_list) {
  token temp = stack_list->token_list[stack_list->count_token];
  stack_list->token_list[stack_list->count_token].ptr = NULL;
  stack_list->token_list[stack_list->count_token].precedency = 0;
  stack_list->count_token--;
  return temp;
}

char serchFuncs(char *str) {
  char return_value = '\0';
  if (strncmp(str, "sin", 3) == 0) {
    return_value = 's';
  } else if (strncmp(str, "cos", 3) == 0) {
    return_value = 'c';
  } else if (strncmp(str, "tan", 3) == 0) {
    return_value = 't';
  } else if (strncmp(str, "log", 3) == 0) {
    return_value = 'L';
  } else if (strncmp(str, "sqrt", 4) == 0) {
    return_value = 'q';
  } else if (strncmp(str, "ln", 2) == 0) {
    return_value = 'l';
  } else if (strncmp(str, "atan", 4) == 0) {
    return_value = 'T';
  } else if (strncmp(str, "acos", 4) == 0) {
    return_value = 'C';
  } else if (strncmp(str, "asin", 4) == 0) {
    return_value = 'S';
  }
  return return_value;
}

void makeList(char *str, list *infix) {
  token input_value = {0, NULL};
  while (*str) {
    if (isdigit(*str)) {
      input_value.ptr = str;
      input_value.precedency = NUM;
      pushList(infix, input_value);
      str++;
      while (isdigit(*str) || *str == '.') {
        str++;
      }
    } else if (*str == '+' || *str == '-') {
      input_value.ptr = str;
      input_value.precedency = ADD;
      pushList(infix, input_value);
      str++;
    } else if (*str == '*' || *str == '/' || *str == '%') {
      input_value.ptr = str;
      input_value.precedency = MUL;
      pushList(infix, input_value);
      str++;
    } else if (*str == '^') {
      input_value.ptr = str;
      input_value.precedency = POW;
      pushList(infix, input_value);
      str++;
    } else if (*str >= 'a' && *str <= 'z') {
      input_value.ptr = str;
      input_value.precedency = FUNC;
      pushList(infix, input_value);
      while (*str >= 'a' && *str <= 'z') {
        str++;
      }
    } else if (*str == '(') {
      input_value.ptr = str;
      input_value.precedency = OP_BR;
      pushList(infix, input_value);
      str++;
    } else if (*str == ')') {
      input_value.ptr = str;
      input_value.precedency = CL_BR;
      pushList(infix, input_value);
      str++;
    }
  }
}

void reversePolishNotation(list *infix, list *polish) {
  list tmp_list = {{{.precedency = 0, .ptr = NULL}}, -1};
  token zero_token = {0, NULL};
  const char *zero_str = "0";
  int count_loop = infix->count_token;
  for (int i = 0; i <= count_loop; i++) {
    if (infix->token_list[i].precedency == OP_BR) {
      pushList(&tmp_list, infix->token_list[i]);
    } else if (infix->token_list[i].precedency == ADD && i == 0) {
      zero_token.precedency = NUM;
      zero_token.ptr = (char *)zero_str;
      pushList(polish, zero_token);
      pushList(&tmp_list, infix->token_list[i]);
    } else if (infix->token_list[i].precedency == CL_BR) {
      while (tmp_list.token_list[tmp_list.count_token].precedency != OP_BR) {
        pushList(polish, tmp_list.token_list[tmp_list.count_token]);
        popList(&tmp_list);
      }
      popList(&tmp_list);
    } else if (infix->token_list[i].precedency == FUNC) {
      pushList(&tmp_list, infix->token_list[i]);
    } else if (infix->token_list[i].precedency == NUM) {
      pushList(polish, infix->token_list[i]);
    } else if (i && ((infix->token_list[i - 1].precedency == OP_BR) &&
                     infix->token_list[i].precedency == ADD)) {
      zero_token.precedency = NUM;
      zero_token.ptr = (char *)zero_str;
      pushList(polish, zero_token);
      pushList(&tmp_list, infix->token_list[i]);
    } else {
      if (tmp_list.count_token == -1) {
        pushList(&tmp_list, infix->token_list[i]);
      } else if (tmp_list.token_list[tmp_list.count_token].precedency != 0 &&
                 infix->token_list[i].precedency != 0) {
        while (((tmp_list.token_list[tmp_list.count_token].precedency >=
                 infix->token_list[i].precedency))) {
          pushList(polish, tmp_list.token_list[tmp_list.count_token]);
          popList(&tmp_list);
        }
        pushList(&tmp_list, infix->token_list[i]);
      }
    }
  }
  while (tmp_list.count_token > -1) {
    pushList(polish, tmp_list.token_list[tmp_list.count_token]);
    popList(&tmp_list);
  }
}

double isOperation(char op, double operand1, double operand2) {
  double result = 0.0;
  switch (op) {
    case '+':
      result = operand1 + operand2;
      break;
    case '-':
      result = operand1 - operand2;
      break;
    case '*':
      result = operand1 * operand2;
      break;
    case '/':
      result = operand1 / operand2;
      break;
    case '^':
      result = pow(operand1, operand2);
      break;
    case '%':
      result = fmod(operand1, operand2);
      break;
  }
  return result;
}

double isFunc(char *op, double operand) {
  double result = 0.0;
  switch (*op) {
    case 's':
      result = sin(operand);
      break;
    case 'c':
      result = cos(operand);
      break;
    case 't':
      result = tan(operand);
      break;
    case 'l':
      result = log(operand);
      break;
    case 'q':
      result = sqrt(operand);
      break;
    case 'L':
      result = log10(operand);
      break;
    case 'T':
      result = atan(operand);
      break;
    case 'C':
      result = acos(operand);
      break;
    case 'S':
      result = asin(operand);
      break;
  }
  return result;
}

double calc(list *polish, double *result) {
  int loop_count = polish->count_token;
  stackD *num = {0};
  for (int i = 0; i <= loop_count; i++) {
    if (polish->token_list[i].precedency == NUM) {
      double number =
          strtod(polish->token_list[i].ptr, &polish->token_list[i].ptr);
      pushDouble(&num, &number);
    } else if (polish->token_list[i].precedency == ADD ||
               polish->token_list[i].precedency == MUL ||
               polish->token_list[i].precedency == POW) {
      double operand2 = popDouble(&num);
      double operand1 = popDouble(&num);
      double number =
          isOperation(*polish->token_list[i].ptr, operand1, operand2);
      pushDouble(&num, &number);
    } else if (polish->token_list[i].precedency == FUNC) {
      double operand1 = popDouble(&num);
      char func = serchFuncs(polish->token_list[i].ptr);
      double number = isFunc(&func, operand1);
      pushDouble(&num, &number);
    }
  }
  return *result = popDouble(&num);
}

double toQt(const char *str, double *answer) {
  char my_str[MAX_SIZE] = {0};
  strcat(my_str, str);
  list infix = {{{.precedency = 0, .ptr = NULL}}, -1};
  list polish = {{{.precedency = 0, .ptr = NULL}}, -1};
  makeList(my_str, &infix);
  reversePolishNotation(&infix, &polish);
  calc(&polish, answer);
  return *answer;
}
