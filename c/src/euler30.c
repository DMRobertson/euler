//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include "integer_powers.c"

/* Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits. */

bool number_is_digit_power_sum(unsigned N, unsigned power){
	unsigned original = N;
	unsigned sum = 0;
	while (N > 0){
		unsigned digit = N % 10;
		sum += powi(digit, power);
		if (sum > original){
			return false;
		}
		N /= 10;
	}
	return sum == original;
}

unsigned get_bound(unsigned power){
	/* Let f(N) = f(a_1a_2...a_n) =  a_1^p + ... + a_n^p for an integer power p. 
	On the range [100...0, 999...9], we have f(N) <= n*9^p.
	We want this to be equal to N, which is bounded below by 10^(n-1) <= N.
	Thus it will be neccesary that 10^(n-1) <= n*9^p.
	This fails when
		10^(n-1) > n * 9^p
		10^n     > n * 10 * 9^p
		n log 10 > log n + log(10*9^p)
		n - (log n)/(log 10) > log(10*9^p)/(log 10)
		n - log_10 n > log_10(10*9^p)
		n - log_10 n > 1 + 9 log(p)
	*/
	double target = log10(10*powi(9, power));
	double n = 1;
	while (n - log10(n) <= target){
		n += 1.0;
	}
	//No need to check numbers this or larger
	return powi(10, (unsigned) n);
}

unsigned sum_equal_digit_power(unsigned power){
	unsigned sum = 0;
	unsigned end = get_bound(power);
	for(unsigned N = 2; N < end; N++){
		if (number_is_digit_power_sum(N, power)){
			sum += N;
		}
	}
	return sum;
}

int main(){
	assert(19316 == sum_equal_digit_power(4));
	printf("%u\n", sum_equal_digit_power(5));
	return 0;
}