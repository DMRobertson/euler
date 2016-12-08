#ifndef INTEGER_MATHS_
#define INTEGER_MATHS_

#include <stdlib.h>
#include <stdbool.h>
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
		//TODO: detect overflow when multiplying accumlator
		accumlator *= base;
		length++;
	}
	return length;
}

unsigned smallest_power_above(unsigned n, unsigned base){
	assert(base > 1);
	unsigned accumlator = 1;
	while (accumlator <= n){
		accumlator *= base;
	}
	return(accumlator);
}

unsigned largest_power_below(unsigned n, unsigned base){
	return smallest_power_above(n, base) / base;
}

unsigned nth_digit(unsigned number, unsigned base, unsigned target_digit){
	assert(base > 1);
	unsigned cmp = base;
	unsigned digits = 1;
	while (cmp <= number){
		cmp *= base;
		digits++;
	}
	while (digits > target_digit){
		number /= base;
		digits--;
	}
	return number % base;
}

void record_digits(unsigned number, unsigned base, unsigned* digits){
	// C standard imposes that (unsigned) ints are at least 16 bits long
	assert(base > 1 && base <= 16);
	while (number){
		*digits |= 1 << (number % base);
		number /= base;
	}
}

bool is_pandigital_one_to(unsigned number, unsigned base, unsigned limit){
	unsigned digits = 0;
	record_digits(number, base, &digits);
	unsigned mask = (1 << (limit + 1)) - 2;
	return digits == mask;
}

bool is_pandigital(unsigned number, unsigned base){
	return is_pandigital_one_to(number, base, digit_length(number, base));
}

#endif // INTEGER_MATHS_