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

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {

  My_string* mystringp = (My_string*)hMy_string;

  char* temp_arr;
  char c;
  
  int i; //counter for for loops
  int count = 0; //counter for array
  int wsp; //whitespace
  
  mystringp->size = 0; //prof additions
  
  wsp = fscanf(fp, " %c", &c);
  
  if (wsp == 1 && wsp != EOF) {
  
    //anti-stop condition
    while (c != ' ' && c != EOF && c != '\n') {
      
      if (mystringp->capacity <= mystringp->size) { //resize when capacity = size
      
        temp_arr = (char*)malloc(sizeof(char) * 2 * mystringp->capacity);
      
        for (i = 0; i < mystringp->capacity; i++) { //copy to new arr
          
          temp_arr[i] = mystringp->data[i];
          
        }
      
        free(mystringp->data); //free old data
        mystringp->data = NULL;
        
        mystringp->data = temp_arr;
        //temp_arr = NULL;
        mystringp->capacity = mystringp->capacity * 2;
        
        //free(temp_arr);  
                
      }
    
    mystringp->data[count] = c;
    mystringp->size = count + 1;
    count++;
    
    c = fgetc(fp);
    }
  
    ungetc(c, fp);
    return SUCCESS;
    
  } else {
  
  return FAILURE;
  }

}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {

  My_string* mystringp = (My_string*) hMy_string;
  
  int i;
  
  for (i = 0; i < mystringp->size; i++) { //prints chars store in mystringp->data
  
    fprintf(fp, "%c", mystringp->data[i]);
  
  }

  return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {

    My_string* pMy_String = (My_string*)hMy_string;

    if (pMy_String->size + 1 >= pMy_String->capacity) {

        char* newChar = (char*)malloc(sizeof(char*) * (pMy_String->capacity * 2));

        if (newChar == NULL) {

            return FAILURE;

        }

        for (int i = 0; i <= pMy_String->size; i++) {

            newChar[i] = pMy_String->data[i];
        }

        free(pMy_String->data);

        pMy_String->data = newChar;
        pMy_String->capacity *= 2;

    }

    pMy_String->data[pMy_String->size] = item;
    pMy_String->size = pMy_String->size + 1;

    return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {

    My_string* pMy_String = (My_string*)hMy_string;

    if (pMy_String->size == 0) {

        return FAILURE;
    }

    pMy_String->data[pMy_String->size - 1] = ' ';
    pMy_String->size = pMy_String->size - 1;

    return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
 
    My_string* pMy_String = (My_string*)hMy_string;

    if (index >= pMy_String->size) {

        return NULL;
    }

    return &(pMy_String->data[index]); 
    
}

char* my_string_c_str(MY_STRING hMy_string) {

   My_string* pMy_String = (My_string*)hMy_string; 
   
   if (pMy_String->capacity <= pMy_String->size) {
   
     pMy_String->data[pMy_String->size] = '\0'; //make if statement checking if arr is full
    
   }
    
   return &(pMy_String->data[0]);
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {

    My_string* result = (My_string*)hResult;
    My_string* append = (My_string*)hAppend;

    if (result->size + append->size > result->capacity) {

        char* newChar = (char*)malloc(sizeof(char) * (result->size + append->size));

        if (newChar == NULL) {

            return FAILURE;
        }

        for (int i = 0; i < result->size; i++) {

            newChar[i] = result->data[i];

        }

        free(result->data);
        result->data = newChar;
        result->capacity = (result->size + append->size);
    }

    for (int i = 0; i < append->size; i++) {

        result->data[i + result->size] = append->data[i];

    }

    result->size = (result->size + append->size);

    return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {

    My_string* pMy_String = (My_string*)hMy_string;

    if (pMy_String->size == 0) {

        return TRUE;
    }
    
    return FALSE;
}