#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

unsigned max(unsigned a, unsigned b){
	return a < b ? b : a;
}

unsigned collatz_length(unsigned n, unsigned* cache, size_t cache_length){
	unsigned length = 0;
	const unsigned original_n = n;
	while (n >= cache_length || cache[n] == 0){
		length++;
		if (n % 2 == 0){
			n /= 2;
		} else {
			n = 3*n + 1;
		}
	}
	cache[original_n] = cache[n] + length;
	return cache[original_n];
}

unsigned int max_collatz_chain(unsigned limit, unsigned* cache){
	unsigned max_length = 0;
	unsigned length;
	unsigned owner = 0;
	
	for (unsigned i = 1; i < limit; i++){
		length = collatz_length(i, cache, limit);
		if (length > max_length){
			owner = i;
			max_length = length;
		}
	}
	return owner;
}

int main(){
	unsigned limit = 1000000;
	unsigned* cache = calloc(limit, sizeof(unsigned));
	cache[1] = 1;
	
	assert(collatz_length(13, cache, limit) == 10);
	printf("%u\n", max_collatz_chain(limit, cache));
	return 0;
}