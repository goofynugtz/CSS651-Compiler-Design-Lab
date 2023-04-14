%{
#include <stdio.h>
#include <string.h>
void keywords(char *str);
void operators(char *str);
void identifiers(char *str);
void specialChar(char *str);
void constants(char *str);
int operatorCount = 0;
int identifierCount = 0;
int keywordCount = 0;
int specialCharCount = 0;
int constantCount = 0;
%}
%%
^if$|^else$|^while$|^do$|^for$   { keywords(yytext);    }
[a-zA-Z_]+[a-zA-Z_0-9]*          { identifiers(yytext); }
[\();\{}]?                       { specialChar(yytext); }
==|[+\-*/=]?                     { operators(yytext);   }
[0-9]*                           { constants(yytext);   }
.                                {                      }
%%
int main(int argc, char *argv[]){
  if (argc != 2){
    printf("Usage: <./a.out> <source file>\n");
    exit(0);
  }
  yyin = fopen(argv[1], "r");
  yylex();
  printf("\nOperator count: %d\n", operatorCount);
  printf("\nIdentifier count: %d\n", identifierCount);
  printf("\nSpecial Char count: %d\n", specialCharCount);
  printf("\nConstant count: %d\n\n", constantCount);
  return 0;
}
void keywords(char *str){
  keywordCount++;
  printf("Keyword %s\n", str);
}
void operators(char *str){
  operatorCount++;
  printf("Operator: %s\n", str);
}
void constants(char *str){
  constantCount++;
  printf("Constant : %s\n", str);
}
void identifiers(char *str){
  identifierCount++;
  printf("Identifier %s\n", str);
}
void specialChar(char *str){
  specialCharCount++;
  printf("Special Char: %s\n", str);
}