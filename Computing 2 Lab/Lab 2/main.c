#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]) {

	MY_STRING hMy_string = NULL;

	hMy_string = my_string_init_default();

	printf("capacity = %d\n", my_string_get_capacity(hMy_string));
	printf("size = %d\n", my_string_get_size(hMy_string));

	MY_STRING hLeftString = my_string_init_c_string("Moskva");
	MY_STRING hRightString = my_string_init_c_string("moskva");

	printf("String compare = %d\n", my_string_compare(hLeftString, hRightString));

	my_string_destroy(&hMy_string);

	my_string_destroy(&hLeftString);
	my_string_destroy(&hRightString);

	return 0;
}
