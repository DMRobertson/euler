#include <stdio.h>
#include <assert.h>

#define NUM_DIGITS 1000

/*
The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.
Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?
*/
long unsigned max(long unsigned a, long unsigned b){
	return a < b ? b : a;
}

long unsigned sweep(unsigned* array, size_t index, size_t num_factors){
	long unsigned prod = 1;
	for (size_t j = 0; j < num_factors; j++){
		prod *= array[index + j];
	}
	return prod;
}

long unsigned max_moving_product(unsigned* array, size_t array_length, size_t num_factors){
	long unsigned max_prod = 0;
	size_t limit = array_length - num_factors;
	for (size_t i = 0; i <= limit; i++){
		max_prod = max(max_prod, sweep(array, i, num_factors));
	}
	return max_prod;
}

void setup(unsigned* data, char const* filename){
	char buffer [NUM_DIGITS];
	FILE* source = fopen(filename, "r");
	fread(buffer, sizeof(char), NUM_DIGITS, source);
	fclose(source);
	for (int i = 0; i < NUM_DIGITS; i += 1){
			data[i] = buffer[i] - '0';
	}
}

int main(){
	unsigned data[NUM_DIGITS];
	setup(data, "../resource/problem8.num");
	assert(max_moving_product(data, NUM_DIGITS, 4) == 5832);
	printf("%lu\n", max_moving_product(data, NUM_DIGITS, 13));
	return 0;
}