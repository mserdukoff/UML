#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include "generic.h"

int main(int argc, char* argv[]) {

  int i;

  MY_STRING mystring = my_string_init_c_string("");
  GENERIC_VECTOR arr_of_vects[30];
  
  FILE *fp = fopen("dictionary.txt", "r");
  
  //check if file opens
  if (fp == NULL) {
  
    printf("File failed to open.\n");
    
    exit(1);
  }
  
  //create the data structure
  for (i = 0; i < 30; i++) {
    
    arr_of_vects[i] = generic_vector_init_default(my_string_assignment, my_string_destroy); 
  }
    
  while (my_string_extraction(mystring, fp)) {
    
    
    generic_vector_push_back(arr_of_vects[my_string_get_size(mystring)], mystring);
  }
    
  for (i = 0; i < 30; i++) {
    
    printf("The vector with index %d has %d items\n", i, generic_vector_get_size(arr_of_vects[i]));
    
  }
  
  my_string_destroy(&mystring);
  
  for (i = 0; i < 30; i++) {
  
    generic_vector_destroy(&arr_of_vects[i]);
  }
  
  fclose(fp);
  fp = NULL;
  
  return 0;  
}
  