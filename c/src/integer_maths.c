#ifndef INTEGER_MATHS_
#define INTEGER_MATHS_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>

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
	return ceil(log(n+1) / log(base));
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

void record_digits(long unsigned number, unsigned base, unsigned* digits){
	// C standard imposes that (unsigned) ints are at least 16 bits long
	assert(base > 1 && base <= 16);
	while (number){
		*digits |= 1 << (number % base);
		number /= base;
	}
}

unsigned char* count_digits(long unsigned number, unsigned base){
	assert(base > 1);
	unsigned char* counts = calloc( base, sizeof(unsigned char) );
	while (number){
		unsigned digit = number % base;
		counts[digit]++;
		number /= base;
	}
	return counts;
}

bool equal_digit_counts(unsigned char* first, unsigned char* second, unsigned base){
	for(size_t i = 0; i < base; i++){
		if (first[i] != second[i]){
			return false;
		}
	}
	return true;
}

bool is_pandigital_one_to(unsigned number, unsigned base, unsigned limit){
	unsigned digits = 0;
	record_digits(number, base, &digits);
	// get 11111...11 as 2^k - 1 for some k. Then remove two to get the mask
	// Example: For 1-to-5 pandigital
	// 1000000 is 1 << 6
	//  111111 subtract 1 to get ones below
	//  111110 subtract 1 to remove the bit corresponding to the zero digit
	//  543210 corresponding digits
	unsigned mask = (1 << (limit + 1)) - 2;
	return digits == mask;
}

bool is_pandigital_zero_to(long unsigned number, unsigned base, unsigned limit){
	unsigned digits = 0;
	record_digits(number, base, &digits);
	// TODO: the only difference is a -1 instead of a -2 on this line. Is there a way of having an optional boolean argument 'from_zero'?
	unsigned mask = (1 << (limit + 1)) - 1;
	return digits == mask;
}

bool is_pandigital(unsigned number, unsigned base){
	return is_pandigital_one_to(number, base, digit_length(number, base));
}

bool is_square(unsigned number){
	//http://stackoverflow.com/a/22239147/5252017
	//Apparently as long as the number isn't too big relative to the accuracy of the floats your using, this gives equal precision to using integer arithmetic.
	//Assuming doubles are IEEE 754 doubles, this should be fine for number <= 2^53
	double root = sqrt(number);
	return root * root == number;
}

#endif // INTEGER_MATHS_