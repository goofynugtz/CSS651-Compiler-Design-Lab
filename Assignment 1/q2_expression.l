%{
#include <stdio.h>
void operators(char *);
void specialChar(char *);
void identifiers(char *);
void constants(char *);
int identifierCount = 0;
int operatorCount = 0;
int specialCharCount = 0;
int constantCount = 0;
int tokenCount = 0;
%}

%%
[a-zA-Z_]+[a-zA-Z_0-9]*    { identifiers(yytext); }
[+\-*/=^]?                 { operators(yytext);   }
[\(\)]?                    { specialChar(yytext); }
[0-9]*                     { constants(yytext);   }
%%

int main(int argc, char *argv[]){
  if (argc != 2){
    printf("Usage: <./a.out> <source file>\n");
    exit(0);
  }
  yyin = fopen(argv[1], "r");
  FILE *fp;
  fp = fopen("unsigned.txt", "w");
  fclose(fp);
  yylex();
  printf("\nOperator count: %d\n", operatorCount);
  printf("\nIdentifier count: %d\n", identifierCount);
  printf("\nSpecial Char count: %d\n", specialCharCount);
  printf("\nConstant count: %d\n", constantCount);
  printf("\nToken count: %d\n", tokenCount);
  return 0;
}

void identifiers(char *str){
  identifierCount++; tokenCount++;
  printf("Identifier: %s\n", str);
}
void operators(char *str){
  operatorCount++; tokenCount++;
  printf("Operator: %s\n", str);
}
void specialChar(char *str){
  specialCharCount++; tokenCount++;
  printf("Special Char: %s\n", str);
}
void constants(char *str){
  constantCount++; tokenCount++;
  printf("Constant : %s\n", str);
}
