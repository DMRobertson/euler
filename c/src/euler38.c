//prepare: -lm

#include <stdio.h>
#include <assert.h>
#include "integer_maths.c"

/* Take the number 192 and multiply it by each of 1, 2, and 3:
	192 × 1 = 192
	192 × 2 = 384
	192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

// multipliers: a 0-terminated list of integers
unsigned concatenated_product(unsigned base, unsigned upto){
	unsigned result = 0;
	for (unsigned i = 1; i <= upto; i++){
		unsigned term = base * i;
		unsigned shift = smallest_power_above(term, 10);
		result *= shift;
		result += term;
	}
	return result;
}

unsigned largest_pandigital_concatenated_product(unsigned limit){
	unsigned max_pandigital = 0;
	unsigned max_result = powi(10, limit);
	for (unsigned i = limit; i >= 2; i--){
		unsigned result = 0;
		for (unsigned multiplicand = 1; result < max_result; multiplicand++){
			result = concatenated_product(multiplicand, i);
			if (result > max_pandigital && is_pandigital_one_to(result, 10, 9)){
				max_pandigital = result;
			}
		}
	}
	return max_pandigital;
}

int main(){
	assert(concatenated_product(192, 3) == 192384576);
	assert(is_pandigital_one_to(192384576, 10, 9));
	assert(concatenated_product(9, 5) == 918273645);
	assert(is_pandigital_one_to(918273645, 10, 9));
	printf("%u\n", largest_pandigital_concatenated_product(9));
	return 0;
}