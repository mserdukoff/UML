#ifndef MY_STRING_H
#define MY_STRING_H

typedef void* MY_STRING;

typedef enum {FAILURE, SUCCESS} Status;

MY_STRING my_string_init_default(void);

void my_string_destroy(MY_STRING* phMy_string);

MY_STRING my_string_init_c_string(const char* c_string);

int my_string_get_capacity(MY_STRING hMy_string);

int my_string_get_size(MY_STRING hMy_string);

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

//Lab 3

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

Status my_string_insertion(MY_STRING hMY_string, FILE* fp);

//Lab 4

Status my_string_push_back(MY_STRING hMy_string, char item);

Status my_string_pop_back(MY_STRING hMy_string);

char* my_string_at(MY_STRING hMy_string, int index);

char* my_string_c_str(MY_STRING hMy_string);

Status my_string_constant(MY_STRING hResult, MY_STRING hAppend);

Boolean my_string_empty(MY_STRING hMy_string);

#endif
