#include <stdio.h>                                                                                                
#include "my_string.h"

int main(int argc, char* argv[]) {

  

  int i;
  int count;

  MY_STRING arrstr[100];

  for (i = 0; i < 100; i++) {
    
    arrstr[i] = NULL;
  }

  arrstr[0] = my_string_init_c_string("COPY ME!");

  for (count = 1; count < 100; count++) {
   
    my_string_assignment(&arrstr[i], arrstr[0]);    
    my_string_insertion(arrstr[i], stdout);
    printf("\n");                                             
  }
  
  printf("\n");
  printf("\n");
  
  for (i = 0; i < 100; i++) {
    
    printf("Here1 %d\n", i);
    my_string_insertion(arrstr[i], stdout);
    printf("\nHere2 %d\n", i);
    printf("\ni = %d\n", i);
    my_string_destroy(&arrstr[i]);
  }
  

  
  /*
  MY_STRING h1 = NULL;
  MY_STRING h2 = my_string_init_c_string("COPY ME!");
  
  my_string_assignment(&h1, h2);
  
  printf("%d\n", my_string_get_size(h1));
  printf("%d\n", my_string_get_capacity(h1));
  
  my_string_insertion(h1, stdout);
  
  printf("\n");
  
  */
  
  return 0;
}