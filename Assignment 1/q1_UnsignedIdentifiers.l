%{

#include <stdio.h>
void appendUnsignedNumbers(char *);
void identifiers(char *);
int unsignedNumbers = 0;
int identifierCount = 0;

%}
%%

^[+]?[0-9]+([\.][0-9]+)?([eE][+-]?[0-9]+)?$ { appendUnsignedNumbers(yytext); }
^[a-zA-Z_]+[a-zA-Z_0-9]*$                   { identifiers(yytext); }

%%

int main(int argc, char *argv[]){
  if (argc != 2){
    printf("Usage: <./a.out> <source file>\n");
    exit(0);
  }
  yyin = fopen(argv[1], "r");
  FILE *fp;
  fp = fopen("unsigned.txt", "w");
  fp = fopen("identifier.txt", "w");
  fclose(fp);
  yylex();
  printf("\nUnsigned Number count: %d\n", unsignedNumbers);
  printf("\nIdentifier count: %d\n", identifierCount);
  return 0;
}

void appendUnsignedNumbers(char *str){
  unsignedNumbers++;
  FILE *fp;
  fp = fopen("unsigned.txt", "a");
  fprintf(fp, "%s\n", str);
  fclose(fp);
}

void identifiers(char *str){
  identifierCount++;
  FILE *fp;
  fp = fopen("identifier.txt", "a");
  fprintf(fp, "%s\n", str);
  fclose(fp);
}