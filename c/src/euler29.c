//prepare: -lgmp

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <gmp.h>

/* Consider all integer combinations of a^b for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

2^2=4,  2^3=8,   2^4=16,  2^5=32
3^2=9,  3^3=27,  3^4=81,  3^5=243
4^2=16, 4^3=64,  4^4=256, 4^5=1024
5^2=25, 5^3=125, 5^4=625, 5^5=3125
If they are then placed in numerical order, with any repeats removed, we get the following sequence of 15 distinct terms:

4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

How many distinct terms are in the sequence generated by a^b for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100? */

size_t seq_power_seq(mpz_t** output_addr, unsigned base_initial, unsigned base_final, unsigned exp_initial, unsigned exp_final){
	assert(base_final > base_initial);
	assert( exp_final >  exp_initial);
	size_t index = 0;
	size_t length = (1 + exp_final - exp_initial) * (1 + base_final - base_initial);
	mpz_t* output = malloc( sizeof(mpz_t) * length );
	for (unsigned a = base_initial; a <= base_final; a++){
		mpz_init(output[index]);
		mpz_ui_pow_ui(output[index], a, exp_initial);
		index++;
		for (unsigned b = exp_initial + 1; b <= exp_final; b++){
			mpz_init(output[index]);
			mpz_mul_ui(output[index], output[index-1], a);
			index++;
		}
	}
	*output_addr = output;
	return length;
}

int mpz_comparison(const void* a, const void* b){
	mpz_t* A = (mpz_t*) a;
	mpz_t* B = (mpz_t*) b;
	return mpz_cmp(*A, *B);
}

size_t unique_integer_powers(unsigned base_initial, unsigned base_final, unsigned exp_initial, unsigned exp_final){
	mpz_t* results;
	size_t length = seq_power_seq(&results, base_initial, base_final, exp_initial, exp_final);
	qsort(results, length, sizeof(mpz_t), mpz_comparison);
	
	size_t uniques = 1;
	for (size_t i = 1; i < length; i++){
		int cmp_result = mpz_cmp(results[i], results[i-1]);
		uniques += cmp_result != 0;
	}
	
	for (size_t i = 0; i < length; i++){
		mpz_clear(results[i]);
	}
	free(results);
	return uniques;
}

int main(){
	assert(unique_integer_powers(2, 5, 2, 5) == 15);
	printf("%lu\n", unique_integer_powers(2, 100, 2, 100));
	return 0;
}