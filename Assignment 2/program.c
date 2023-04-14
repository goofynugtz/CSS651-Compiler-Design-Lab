#include<stdio.h>

int main(){
  int a = 0x12345678;
  char *p = (char*)&a;
  if(*p==0x78) printf("Little endian\n");
  else printf("Big endian\n");
  return 0;
}
