%{
#include <stdio.h>
void detectedLUD(char *);
void detectedLD(char *);
void detectedLLUD(char *);

int LUDcount   = 0;
int LDcount    = 0;
int LLUDcount  = 0;
%}

L                       [a-eA-E]
D                       [0-4]

%%
^{L}|{D}$               { detectedLUD(yytext);  }
^{L}{D}$                { detectedLD(yytext);   }
^{L}({L}|{D})$          { detectedLLUD(yytext); }
.                       {                       }
%%
int main(int argc, char *argv[]){
  yylex();
  // printf("\n(L U D) count: %d\n", LUDcount);
  // printf("\n(LD) count: %d\n", LDcount);
  // printf("\nL (L U D) count: %d\n", LLUDcount);
  return 0;
}

void detectedLUD(char *str){
  LUDcount++;
  printf(">> Accepted (L U D)\n");
}
void detectedLD(char *str){
  LDcount++;
  printf(">> Accepted (LD)\n");
}
void detectedLLUD(char *str){
  LLUDcount++;
  printf(">> Accepted L(LUD)\n");
}
