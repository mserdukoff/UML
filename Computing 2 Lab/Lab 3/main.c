#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[]) {

  int s = 5; //can be 5 or 29
  MY_STRING hMy_string = NULL;
  FILE* fp;

  hMy_string = my_string_init_default();

  fp = fopen("dictionary.txt", "r");

  while(my_string_extraction(hMy_string, fp)) {
    
    if (my_string_get_size(hMy_string) == s) {
      
      my_string_insertion(hMy_string, stdout);
      printf("\n");
      
    }
  
  }
  
  my_string_destroy(&hMy_string);
  fclose(fp);
  
  return 0;
}
