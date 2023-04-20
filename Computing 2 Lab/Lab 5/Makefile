CC = gcc -g
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o
LAB_OBJECTS = my_string.o unit_test.o test_def.o

unit_test: $(LAB_OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(LAB_OBJECTS)
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
clean:
	rm unit_test $(LAB_OBJECTS)

