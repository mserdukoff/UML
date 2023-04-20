#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length) { //1 does init_default() work

  MY_STRING hString = NULL;
  hString = my_string_init_default();
  
  if (hString == NULL) {
  
    strncpy(buffer, "test_init_default_returns_nonNULL\n" "my_string_init_default returns NULL", length);
    
    return FAILURE;
  }
  
  else {
  
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    
    return SUCCESS;
  }

}

Status test_get_size_on_init_default_returns_0(char* buffer, int length) { //2 makes sure init_default = 0

  MY_STRING hString = NULL;
  
  Status status;
  
  hString = my_string_init_default();
  
  if (my_string_get_size(hString) != 0) {
  
    status = FAILURE;
    
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n" "Did not receive - from get_size after init_default\n", length);
  }
    
  else {
    
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_get_capacity_on_init_default_returns_non0(char* buffer, int length) { //3  makes sure capacity is not 0
  
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();

  if(my_string_get_capacity(hString) <= 0) {
    
    status = FAILURE;
    
    printf("Expected a size greater than 0 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_mserduko_get_capacity_on_init_default_returns_non0\n"
	    "Received value of 0 or lower from get_capacity after init_default\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_get_capacity_on_init_default_returns_non0\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_init_c_string_returns_nonNULL(char* buffer, int length) { //4 makes sure init_c_string initializes correctly

  MY_STRING hString = NULL;

  hString = my_string_init_c_string("Hello");

  if(hString == NULL) {
  
    strncpy(buffer, "test_mserduko_init_c_string_returns_nonNULL\n"
	    "my_string_init_c_string returns NULL", length);
    return FAILURE;
  }
  else {
  
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_mserduko_init_c_string_returns_nonNULL\n", length);
    
    return SUCCESS;
  }
}

Status test_mserduko_get_capacity_on_init_c_string_returns_non0(char* buffer, int length) { //5 tests capacity of init c string
  
  MY_STRING hString = NULL;
  
  Status status;

  hString = my_string_init_c_string("pies");

  if(my_string_get_capacity(hString) <= 0) {
    
    status = FAILURE;
    printf("Expected a size greater than 0 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_mserduko_get_capacity_on_init_c_string_returns_non0\n"
	    "Received value of 0 or lower from get_capacity after init_c_string\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_get_capacity_on_init_c_string_returns_non0\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}


Status test_mserduko_get_size_on_empty_init_c_string_returns_0(char* buffer, int length) { //6 checks size of an empty string

  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("");

  if(my_string_get_size(hString) != 0) {
  
    status = FAILURE;
    
    printf("Expected a size greater of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_mserduko_get_size_on_empty_init_c_string_returns_0\n"
	    "Received non0 value from get_size after init_c_string\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_get_size_on_empty_init_c_string_returns_0\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_compare_right_bigger_returns_lessthan0(char* buffer, int length) { //7 if right bigger 

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  Status status;

  hString_1 = my_string_init_c_string("Russia");
  hString_2 = my_string_init_c_string("Leningrad");

  if(my_string_compare(hString_1, hString_2) >= 0) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_compare_right_bigger_returns_lessthan0\n"
	    "my_string_compare returns >= 0 while right string is bigger", length);
  }
  
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_compare_right_bigger_returns_lessthan0\n",
	    length);
  }

  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_compare_left_bigger_returns_greaterthan0(char* buffer, int length) { //8 if left bigger

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  Status status;

  hString_1 = my_string_init_c_string("Dinosaur");
  hString_2 = my_string_init_c_string("Cheese");

  if(my_string_compare(hString_1, hString_2) <= 0) {
    
    status = FAILURE;
    strncpy(buffer, "test_mserduko_compare_left_bigger_returns_greaterthan0\n"
	    "my_string_compare returns <= 0 while left string is bigger", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_compare_left_bigger_returns_greaterthan0\n",
	    length);
  }

  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_compare_same_returns_0(char* buffer, int length) { //9 test whether strings are the same

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  Status status;

  hString_1 = my_string_init_c_string("Egg");
  hString_2 = my_string_init_c_string("Egg");

  if(my_string_compare(hString_1, hString_2) != 0) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_compare_same_returns_0\n"
	    "my_string_compare returns non0 while strings are equal", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_compare_same_returns_0\n",
	    length);
  }

  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_compare_same_right_bigger_returns_lessthan0(char* buffer, int length) { //10 right bigger with similar word

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  Status status;

  hString_1 = my_string_init_c_string("Fast");
  hString_2 = my_string_init_c_string("Faster");

  if(my_string_compare(hString_1, hString_2) >= 0) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_compare_same_right_bigger_returns_lessthan0\n"
	    "my_string_compare returns >= 0 while right string is bigger", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_compare_same_right_bigger_returns_lessthan0\n",
	    length);
  }

  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_compare_same_left_bigger_returns_greaterthan0(char* buffer, int length) { //11 left bigger

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  Status status;

  hString_1 = my_string_init_c_string("Smarter");
  hString_2 = my_string_init_c_string("Smart");

  if(my_string_compare(hString_1, hString_2) <= 0) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_compare_same_left_bigger_returns_greaterthan0\n"
	    "my_string_compare returns <= 0 while left string is bigger", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_compare_same_left_bigger_returns_greaterthan0\n",
	    length);
  }

  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_push_back_increments_size(char* buffer, int length) { //12 checks size increase of push

  MY_STRING hString = NULL;
  
  Status status;
  
  char item, size, push_size;

  hString = my_string_init_default();
  item = 'd';

  size = my_string_get_size(hString);
  my_string_push_back(hString, item);
  push_size = my_string_get_size(hString);

  if(push_size != (size + 1)) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_push_back_increments_size\n"
	    "my_string_push_back does not increment size", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_push_back_increments_size\n",
	    length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_concat_capacity_greaterthan_combined_arg_size(char* buffer, int length) { //13 tests if capacity of combined strings is smaller than necessary

  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  int combined_size;
  int concat_capacity;
  
  Status status;

  hString_1 = my_string_init_c_string("hello");
  hString_2 = my_string_init_c_string("there");

  combined_size = (my_string_get_size(hString_1) + my_string_get_size(hString_2));
  my_string_concat(hString_1, hString_2);
  concat_capacity = (my_string_get_capacity(hString_1));

  if(concat_capacity < combined_size) { //changed <= to <, then worked
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_concat_capacity_greaterthan_combined_arg_size\n"
	    "capacity of concat strings smaller than combined size of strings", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_concat_capacity_greaterthan_combined_arg_size\n",
	    length);
  }
  
  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_concat_size_equalto_combined_arg_size(char* buffer, int length) { //14 checks if concat size is correct when combined
  
  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  int combined_size;
  int concat_size;
  
  Status status;

  hString_1 = my_string_init_c_string("hello");
  hString_2 = my_string_init_c_string("there");

  combined_size = (my_string_get_size(hString_1) + my_string_get_size(hString_2));
  my_string_concat(hString_1, hString_2);
  concat_size = (my_string_get_size(hString_1));

  if(concat_size != combined_size) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_concat_size_equalto_combined_arg_size\n"
	    "size of concat strings not equal to combined size of strings", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_concat_size_equalto_combined_arg_size\n",
	    length);
  }
  
  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_concat_does_not_change_append_string_size(char* buffer, int length) { //15 makes sure size does not change
  
  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  int append_size;
  int append_size_after_concat;
  
  Status status;

  hString_1 = my_string_init_c_string("eeee");
  hString_2 = my_string_init_c_string("ffff");

  append_size = my_string_get_size(hString_2);
  my_string_concat(hString_1, hString_2);
  append_size_after_concat = my_string_get_size(hString_2);

  if(append_size != append_size_after_concat) { 
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_concat_does_not_change_append_string_size\n"
	    "size of append changes after string concat", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_concat_does_not_change_append_string_size\n",
	    length);
  }
  
  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_concat_does_not_change_append_string_capacity(char* buffer, int length) { //16
  
  MY_STRING hString_1 = NULL;
  MY_STRING hString_2 = NULL;
  
  int append_capacity;
  int append_capacity_after_concat;
  
  Status status;

  hString_1 = my_string_init_c_string("hello");
  hString_2 = my_string_init_c_string("there");

  append_capacity = my_string_get_capacity(hString_2);
  my_string_concat(hString_1, hString_2);
  append_capacity_after_concat = my_string_get_capacity(hString_2);

  if(append_capacity != append_capacity_after_concat) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_concat_does_not_change_append_string_capacity\n"
	    "capacity of append changes after string concat", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_concat_does_not_change_append_string_capacity\n",
	    length);
  }
  
  my_string_destroy(&hString_1);
  my_string_destroy(&hString_2);
  
  return status;
}

Status test_mserduko_string_empty_on_init_default_returns_1(char* buffer, int length) { //17 tests if default is empty after my_string_empty
  
  MY_STRING hString = NULL;
  
  Status status;

  hString = my_string_init_default();

  if(my_string_empty(hString) == 1) {
  
    status = SUCCESS;
    
    strncpy(buffer, "\ttest_mserduko_string_empty_on_init_default_returns_1\n",length);
  }
  else {
  
    status = FAILURE;
    
    strncpy(buffer, "test_mserduko_string_empty_on_init_default_returns_1\n"
	    "Received value of 0 for isEmpty after init default\n", length);   
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_string_empty_on_init_c_string_returns_0(char* buffer, int length) { //18 checks if init_c_string is empty using my_string_empty
  
  MY_STRING hString = NULL;
  
  Status status;

  hString = my_string_init_c_string("hello");

  if(my_string_empty(hString) == 0) {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_string_empty_on_nonEmpty_init_c_string_returns_0\n",length);
  }
  else {
    
    status = FAILURE;
    strncpy(buffer, "test_mserduko_string_empty_on_nonEmpty_init_c_string_returns_0\n"
	    "Received value of 1 for isEmpty after non empty init c string\n", length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_pop_back_decrements_size_on_init_c_string(char* buffer, int length) { //19 checks if size decreases after pop_back

  MY_STRING hString = NULL;
  
  Status status;
  
  int size, popSize;

  hString = my_string_init_c_string("hello");
  
  size = my_string_get_size(hString);
  
  my_string_pop_back(hString);
  
  popSize = my_string_get_size(hString);

  if(popSize >= size) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_pop_back_decrements_size_on_init_c_string\n"
	    "Size was not decremented after pop back\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_pop_back_decrements_size_on_init_c_string\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_pop_back_on_init_default_returns_failure(char* buffer, int length) { //20 tests if an empty string can be popped

  MY_STRING hString = NULL;
  
  Status status;
  
  hString = my_string_init_default();

  if(SUCCESS == my_string_pop_back(hString)) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_pop_back_on_init_default_returns_failure\n"
	    "Pop back returned success on an empty string\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_pop_back_on_init_default_returns_failure\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_c_str_on_init_c_string_returns_nonNULL(char* buffer, int length) { //21 makes sure c_str returns not null on a non empty string
  
  MY_STRING hString = NULL;
  
  Status status;

  hString = my_string_init_c_string("hello");

  if(my_string_c_str(hString) == NULL) {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_c_str_on_init_c_string_returns_nonNULL\n"
	    "c str returns null on nonempty init c string\n", length);
  }
  else {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_c_str_on_init_c_string_returns_nonNULL\n",length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_string_at_on_extra_index_returns_NULL(char* buffer, int length) { //22 tests if an incorrect index will return anything other than null

  MY_STRING hString = NULL;
  
  Status status;
  
  int invalidIndex;

  hString = my_string_init_c_string("hello");
  invalidIndex = my_string_get_size(hString) + 1;

  if(NULL == my_string_at(hString, invalidIndex)) {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_string_at_on_extra_index_returns_NULL\n",length);
  }
  else {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_string_at_on_extra_index_returns_NULL\n"
	    "my string at is nonNull given an extra index\n", length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_string_at_on_negative_index_returns_NULL(char* buffer, int length) { //23 given negative index, return NULL
  
  MY_STRING hString = NULL;
  
  Status status;
  
  int invalidIndex = -1;

  hString = my_string_init_c_string("hello");

  if(my_string_at(hString, invalidIndex)) {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_string_at_on_negative_index_returns_NULL\n",length);
  }
  else {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_string_at_on_negative_index_returns_NULL\n"
	    "my string at is nonNull given a negative index\n", length);
  }
  
  my_string_destroy(&hString);
  
  return status;
}

Status test_mserduko_extraction_returns_success_on_file_read(char* buffer, int length) { //24 if file can be used, return success

  MY_STRING hString = NULL;
  
  FILE* fp;
  
  Status status;

  hString = my_string_init_default();
  fp = fopen("simple.txt", "r");
  
  if(fp == NULL) {
  
    printf("Failure opening file in test_mserduko_extraction_returns_failure_on_EOF");
    return FAILURE;
  }
  
  if(my_string_extraction(hString, fp) == SUCCESS) {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_extraction_returns_success_on_file_read\n",length);
  }
  else {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_extraction_returns_success_on_file_read\n"
	    "String extraction did not return success on file read\n", length);
  }

  my_string_destroy(&hString);
  fclose(fp);
  
  return status;
}

Status test_mserduko_insertion_returns_success_on_writing_to_file(char* buffer, int length) { //25 if string_insertion works with file, return success
  
  MY_STRING hString = NULL;
  
  FILE* fp;
  
  Status status;

  hString = my_string_init_default();
  fp = fopen("simple.txt", "r");
  
  if(fp == NULL) {
    
    printf("Failure opening file in test_mserduko_insertion_returns_success_on_writing_to_file");
    return FAILURE;
  }
  
  if(SUCCESS == my_string_insertion(hString, fp)) {
  
    status = SUCCESS;
    strncpy(buffer, "\ttest_mserduko_insertion_returns_success_on_writing_to_file\n",length);
  }
  else {
  
    status = FAILURE;
    strncpy(buffer, "test_mserduko_insertion_returns_success_on_writing_to_file\n"
	    "String insertion does not return success on file write\n", length);
  }

  fclose(fp);
  my_string_destroy(&hString);
  
  return status;
}