#include <stdio.h>
#include <stdlib.h>

int main() {

	int row; //row
	int column; //collumn

	int x = 0;

	row = 20;
	column = 30;

	int** arr = (int**)malloc(row * sizeof(int*));

	int i; //counter variables
	int j;

	for (i = 0; i < row; i++) {

		arr[i] = (int*)malloc(column * sizeof(int));

	}

	printf("Hello World! I have created a dynamic 2D array of 20 by 30 integers!\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < column; j++) {

			if (j >= 29) {

				arr[i][j] = j + x;
				x += 1;
			}

			arr[i][j] = j + x;
		}
	}

	for (i = 0; i < row; i++) { //printing

		for (j = 0; j < column; j++) {

			if (j >= 29) {

				printf("%2d \n", (arr[i][j]-1));

			}
			else {

				printf("%2d ", (arr[i][j]));

			}
		}
	}

	for (i = 0; i < row; i++) {

		free(arr[i]);

	}

	free(arr);
	return 0;
}
