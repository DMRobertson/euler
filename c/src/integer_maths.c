#ifndef INTEGER_MATHS_
#define INTEGER_MATHS_

#include <stdlib.h>
#include <assert.h>

size_t ceildiv(size_t num, int div){
	// return the ceiling of (num/div) == floor ((num + div - 1)/div)
	return (num + div - 1) / div;
}

//The method of squares, from http://stackoverflow.com/a/101613/5252017
int powi(int base, int exp){
	int result = 1;
	while (exp){
		if (exp & 1){
			result *= base;
		}
		exp >>= 1;
		base *= base;
	}
	return result;
}

unsigned digit_length(unsigned n, unsigned base){
	assert(base > 1);
	unsigned accumlator = base;
	unsigned length = 1;
	while (accumlator <= n){
		accumlator *= base;
		length++;
	}
	return length;
}

unsigned largest_power_below(unsigned n, unsigned base){
	assert(base > 1);
	unsigned accumlator = base;
	while (accumlator <= n){
		accumlator *= base;
	}
	accumlator /= base;
	return(accumlator);
}

#endif // INTEGER_MATHS_