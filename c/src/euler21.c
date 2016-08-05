//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

unsigned sum_proper_divisors(unsigned n){
	if (n <= 1){
		return 0;
	}
	//Add the 1 manually to avoid adding the pair (1, n) as part of the loop.
	unsigned sum = 1;
	unsigned limit = (unsigned) sqrt(n);
	for (unsigned i = 2; i < limit; i++){
		if (n % i == 0){
			sum += i;
			sum += n/i;
		}
	}
	//Only count exact sqrts once
	if (limit * limit == n){
		sum += limit;
	}
	return sum;
}

bool is_amicable(unsigned n){
	unsigned divsum = sum_proper_divisors(n);
	return (divsum != n) && (sum_proper_divisors(divsum) == n);
}

unsigned sum_amicable_under(unsigned limit){
	unsigned sum = 0;
	for (unsigned i = 1; i < limit; i++){
		if (is_amicable(i)){
			sum += i;
		}
	}
	return sum;
}

int main(){
	assert(sum_proper_divisors(220) == 284 && sum_proper_divisors(284) == 220);
	assert(is_amicable(220) && is_amicable(284));
	printf("%d", sum_amicable_under(10000));
}