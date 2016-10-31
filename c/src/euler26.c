#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "packed_bool_array.c"
/*
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

bool already_seen(unsigned digit, barray* digits_seen){
	if (bget(digits_seen, digit)){
		return true;
	} else {
		bset(digits_seen, digit, true);
		return false;
	}
}

unsigned recurring_cycle_length(const unsigned divisor){
	barray* remainders_seen = bool_array(divisor);
	unsigned dividend = 1;
	unsigned quotient;
	
	unsigned target_remainder = 0;
	unsigned target_position  = 0;
	unsigned result;
	do {
		while (dividend < divisor){
			target_position++;
			dividend *= 10;
		}
		quotient  = dividend / divisor;
		// replace dividend with the remainder
		dividend %= divisor;
		if (quotient > 0 && dividend == 0){
			result = 0;
			goto end;
		} else if (already_seen(dividend, remainders_seen)){
			target_remainder = dividend;
			break;
		}
	} while (true);
	
	unsigned position = 0;
	dividend = 1;
	do {
		while (dividend < divisor){
			position++;
			dividend *= 10;
		}
		dividend %= divisor;
		if (dividend == target_remainder){
			break;
		}
	} while (true);
	result = target_position - position;
	
	end:
	free(remainders_seen);
	return result;
}

int main(){
	assert(recurring_cycle_length(2) == 0);
	assert(recurring_cycle_length(3) == 1);
	assert(recurring_cycle_length(6) == 1);
	assert(recurring_cycle_length(7) == 6);
	unsigned max = 0;
	unsigned max_index = 0;
	for (unsigned i = 2; i < 1000; i++){
		unsigned length = recurring_cycle_length(i);
		if (length > max){
			max = length;
			max_index = i;
		}
	}
	printf("%d\n", max_index);
	return 0;
}