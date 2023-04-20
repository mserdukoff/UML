CC = gcc -g
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o
LAB_OBJECTS = my_string.o unit_test.o test_def.o
LAB7_OBJECTS = my_string.o dictionary.o generic_vector.o


string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
clean:
	rm string_driver $(OBJECTS)

################LAB 7#################
lab_71: $(LAB7_OBJECTS)
	$(CC) $(CFLAGS) -o lab_71 $(LAB7_OBJECTS)
dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c -o dictionary.o
my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
generic_vector.o: generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o
clean_71:
	rm lab_71 $(LAB7_OBJECTS)
