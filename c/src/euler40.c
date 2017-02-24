//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include "integer_maths.c"

/* An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101_1_12131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000 */

static unsigned indices[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 0};
static unsigned indices_test[2] = {12, 0};

unsigned champernowne_digits_product(unsigned* indices){
	//indices is a 0-terminated array of strictly increasing integers
	unsigned product = 1;
	unsigned lower_value = 1;
	unsigned upper_value = 10;
	
	unsigned lower_index = 1;
	unsigned delta_index = 9;
	unsigned num_digits  = 1;
	unsigned upper_index = 10;
	
	for (unsigned* target_index = indices; *target_index > 0; target_index++){
		while (*target_index >= upper_index){
			lower_value = upper_value;
			upper_value *= 10;
			
			lower_index = upper_index;
			num_digits++;
			delta_index *= 10;
			upper_index += delta_index * num_digits;
		}
		
		unsigned value  = lower_value + (*target_index - lower_index) / num_digits;
		unsigned offset = 1 + (*target_index - lower_index) % num_digits;
		
		product *= nth_digit(value, 10, offset);
	}
	return product;
}

int main(){
	assert(champernowne_digits_product(indices_test) == 1);
	printf("%u\n", champernowne_digits_product(indices));
	return 0;
}