//prepare: -lgmp

#include <gmp.h>
#include <assert.h>

/* The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 11 + 22 + 33 + ... + 10001000.
*/

void sum_of_self_powers_upto(mpz_t sum, unsigned limit){
	mpz_set_ui(sum, 0);
	mpz_t term;
	mpz_init(term);
	for (unsigned i = 1; i <= limit; i++){
		mpz_ui_pow_ui(term, i, i);
		mpz_add(sum, sum, term);
	}
}

int main(){
	mpz_t sum;
	mpz_init(sum);
	
	mpz_t target;
	mpz_init_set_str(target, "10405071317", 10);
	sum_of_self_powers_upto(sum, 10);
	assert(mpz_cmp(sum, target) == 0);
	mpz_clear(target);
	
	sum_of_self_powers_upto(sum, 1000);
	
	mpz_t modulus;
	mpz_init_set_str(modulus, "10000000000", 10);
	mpz_mod(sum, sum, modulus);
	
	gmp_printf("%Zd\n", sum);
	mpz_clear(sum);
	return 0;
}