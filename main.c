#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void output_array(Array *a); // prototyping
void shift_array(Array *a); // prototyping
Array *average_adjacent(Array *a); // prototyping

int main(int argc, char *argv[]) {

	// Validating the command line inputs
	if (argc != 2) {
		printf("You need to do: %s <array size>\n", argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);
	if (n <= 0) {
		printf("Error! Size must be a positive integer.\n");
		return 1;
	}

	// Allocating the struct and its array
	Array *a = malloc(sizeof(Array));
	if (a == NULL) {
		printf("Error! Memory allocation has failed.\n");
		return 1;
	}

	a->size = n;
	a->data = malloc(n * sizeof(double));
	if (a->data == NULL) {
		printf("Error! Memory allocation has failed.\n");
		free(a);
		return 1;
	}
	
	// Filling the array with some values
	for (int i = 0; i < a->size; i++){
		a->data[i] = i + 1.0;
	}

	// Call the functions and then free the memory
	output_array(a); // prints original: 1 2 3 4 5
	shift_array(a); // shifts a in place: a is permanently changed
	output_array(a); // prints shifted

	Array *avg = average_adjacent(a); // uses the shifted a
	output_array(avg); // outputs the adjacent that uses the shifted a

	free(a->data);
	free(a);
	free(avg->data);
	free(avg);

	return 0;
}

// Functions

void output_array(Array *a) {
	for (int i = 0; i < a->size; i++) {
		printf("%.2f ", a->data[i]);
	}
	printf("\n");
}

void shift_array(Array *a) {
	if (a->size < 2) {
		return;
	}
	double first = a->data[0];
	for (int i = 0; i < a->size - 1; i++) {
		a->data[i] = a->data[i + 1];
	}
	a->data[a->size - 1] = first; // This was a tricky part to try to work out
}

Array *average_adjacent(Array *a) {
	Array *result = malloc(sizeof(Array));
	result->size = a->size/2;
	result->data = malloc(result->size * sizeof(double));

	for (int i = 0; i < result->size; i++) {
		result->data[i] = (a->data[2 * i] + a->data[2 * i + 1]) / 2.0;
	}
	return result;
}
