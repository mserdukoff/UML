#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[]) {

  int i;
    
  MY_STRING hMy_string;

  MY_STRING hMy_string_append;

  hMy_string = my_string_init_c_string("Dinosaur");
  my_string_push_back(hMy_string, 3);
  my_string_pop_back(hMy_string);
  printf("\n my_string_at %c\n", *my_string_at(hMy_string, 5)); 
  my_string_insertion(hMy_string, stdout);
  
  char *pChar = my_string_c_str(hMy_string);
  printf("%s\n", pChar);
  
  my_string_destroy(&hMy_string);
  
  MY_STRING string1 = my_string_init_c_string("Shrek");
  MY_STRING string2 = my_string_init_c_string("Jurassic");
  
  my_string_concat(string1, string2);
  
  my_string_insertion(string1, stdout); 
  
  printf("%d\n", my_string_get_size(string1));
  printf("%d\n", my_string_empty(string1));
  
  my_string_destroy(&string1);
  my_string_destroy(&string2);
  
  MY_STRING mystring = my_string_init_default();
  
  printf("%d\n", my_string_empty(mystring)); 
  
  my_string_destroy(&mystring);

}

