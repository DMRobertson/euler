#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins? */

const unsigned coins[8] = {1, 2, 5, 10, 20, 50, 100, 200};

unsigned number_options(size_t target){
	unsigned* options = malloc(sizeof(unsigned) * (target + 1));
	options[0] = 1;
	memset(options + 1, 0, target * sizeof(unsigned));
	for (size_t j = 0; j < 8; j++){
		unsigned coin = coins[j];
		for (size_t i = coin; i <= target; i++){
			options[i] += options[i-coin];
		}
	}
	unsigned result = options[target];
	free(options);
	return result;
}

int main(){
	printf("%u\n", number_options(200));
}