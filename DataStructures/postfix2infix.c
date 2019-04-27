#include<stdio.h>
#include<stdlib.h>
#include<string.h>

# define MAX 20

char string[MAX], stack[MAX];
int top = -1;

char pop()
{
      return stack[top--];
}

void push(char ch)
{
      stack[++top] = ch;
}

void postfix_to_infix(char exp[])
{
      int i, l;
      char elem, op;
      l = strlen(exp);
      for(i = 0; i < MAX; i++)
      {
            stack[i] = 0;
      }
      printf("Infix exp:\t");
      printf("%c", exp[0]);
      for(i = 1; i < l; i++)
      {
            if(exp[i] == '-' || exp[i] == '/' || exp[i] == '*'|| exp[i] == '+')
            {
                  elem = pop();
                  op = exp[i];
                  printf(" %c %c", op, elem);
            }
            else
                  push(exp[i]);
      }
      printf("%c", exp[top--]);
}

int main()
{
      char postfix_expression[50];
      printf("Enter Postfix :\t");
      scanf("%s", postfix_expression);
      postfix_to_infix(postfix_expression);
      printf("\n");
      return 0;
}