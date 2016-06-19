#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

size_t ceildiv(size_t num, int div){
	// return the ceiling of (num/div) == floor ((num + div - 1)/div)
	return (num + div - 1) / div;
}

typedef struct packed_bool_array {
	// An array of booleans stored in the bits of chars in memeory
	size_t boollength;
	size_t charlength;
	unsigned char* array;
} barray;


barray bool_array(size_t length){
	/* Efficiently store an array of booleans by packing as many bools as we can get away with into a char. */
	size_t charlength = ceildiv(length, CHAR_BIT);
	unsigned char* array = (unsigned char*) malloc( sizeof(unsigned char) * charlength );
	barray output = {length, charlength, array};
	return output;
}

void bsetall(barray &data, unsigned char value){
	memset(data.array, value, data.charlength);
}

bool bget(barray &data, size_t index){
	size_t bitnum = index % CHAR_BIT;
	index /= CHAR_BIT;
	unsigned char mask = (1 << bitnum);
	bool bit = (data.array[index] & mask) != 0;
	return bit;
}

void bset(barray &data, size_t index, bool value){
	unsigned char bitnum = index % CHAR_BIT;
	index /= CHAR_BIT;
	unsigned char mask = (1 << bitnum);
	if (value) {
		data.array[index] |= mask;
	} else {
		data.array[index] &= (mask ^ -1); //I thought this would be -mask but apparently not!
	}
}

size_t sum_sieve_of_erastosthenes(size_t limit){
	barray sieve = bool_array(limit);
	bsetall(sieve, -1); //unsigned -1 has a 1 in every bit
	//1. Perform the sieve.
	size_t upper_bound = ceil( sqrt( (double) limit ));
	for (size_t i = 2; i <= upper_bound; i++){
		if (bget(sieve, i - 2)) {
			for (size_t j = i*i; j <= limit; j += i){
				bset(sieve, j - 2, false);
			}
		}
	}
	//2. How many primes \pi(n) did we find?
	size_t sum = 0;
	size_t num_primes = 0;
	for (size_t i = 2; i <= limit; i++){
		if (bget(sieve, i - 2)) {
			num_primes++;
			sum += i;
		}
	}
	
	//3. Dump all the primes into an array. Use a zero to signify the end of the array.
	// size_t* primes = (size_t*) malloc( sizeof(size_t) * (num_primes + 1) );
	// size_t index = 0;
	// for (size_t k = 2; k <= limit; k++){
	// 	if (bget(sieve, k)) {
	// 		primes[index] = k;
	// 		index++;
	// 	}
	// }
	// primes[index] = 0;
	// return primes;
	
	//size_t sum = 0;
	//for (size_t i = 2; i <= limit; i++){
	//	if (bget(sieve, i - 2)) {
	//		sum += i;
	//	}
	//}
	
	free(sieve.array);
	
	return sum;
}

int main(){
	assert(sum_sieve_of_erastosthenes(10) == 17);
	printf("%li\n", sum_sieve_of_erastosthenes(2000000));
	return 0;
}
