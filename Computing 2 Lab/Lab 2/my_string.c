#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct my_string {

	int size;
	int capacity;
	char* data;

}; typedef struct my_string My_string;

MY_STRING my_string_init_default() {

	My_string* myStringP;

	myStringP = (My_string*)malloc(sizeof(My_string));

	if (myStringP != NULL) {

    myStringP->size = 0;
  	myStringP->capacity = 7;
	  myStringP->data = (char*)malloc(sizeof(char) * myStringP->capacity);
     
  	if (myStringP->data == NULL) {

		  return NULL;
	  }
		
	}

  return (MY_STRING)myStringP;

}

void my_string_destroy(MY_STRING* phMy_string) {

	My_string* pString = (My_string*)*phMy_string;

	free(pString->data);
	free(pString);

	*phMy_string = NULL;
}
   
MY_STRING my_string_init_c_string(const char* c_string) {

  int x; //size
  int i; //counter

	My_string* myStringP;
 
  x = 1;
 
  for (i = 0; c_string[i] != '\0'; i++) {
    x++;
  }

	myStringP = (My_string*)malloc(sizeof(My_string));
 
  if (myStringP != NULL) {

    myStringP->size = x - 1;
  	myStringP->capacity = x;
	  myStringP->data = (char*)malloc(sizeof(char) * myStringP->capacity);
     
  	if (myStringP->data == NULL) {

      free(myStringP);
		  return NULL;
	  }
		
   
    for (i = 0; i < x; i++) {
    
      myStringP->data[i] = c_string[i];
    
    }
    
	}
  
  return (MY_STRING)myStringP;
}

int my_string_get_capacity(MY_STRING hMy_string) {

  My_string* mystringp = (My_string*) hMy_string;
	return mystringp->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {

  My_string* mystringp = (My_string*) hMy_string;
	return mystringp->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {

  int i;
 
  My_string* l_string = (My_string*)hLeft_string;
  My_string* r_string = (My_string*)hRight_string;

	char* pL_string = l_string->data;
  char* pR_string = r_string->data;
  
  if ((l_string->size) > (r_string->size)) {
  
    printf("Left is longer\n");
    
    return 1;
  }
  
  else if ((l_string->size) < (r_string->size)) {
  
    printf("Right is longer\n");
  
    return -1;
  }
  
  else {
  
    for (i = 0; i < l_string->size; i++) {
    
      printf("%d, %d\n", pL_string[i], pR_string[i]);
      
      if (pL_string[i] > pR_string[i]) {
      
        return 1;
      }
      
      if (pL_string[i] < pR_string[i]) {
      
        return -1;
      }
      
    }
  
  }
  
  return 0; 
}