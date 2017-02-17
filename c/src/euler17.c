#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

#define LEN_THOUSAND 8
#define LEN_HUNDRED  7
#define LEN_AND      3

static unsigned small_numbers[20] = {
	0, // zero has length 4, but we say "twenty" rather than "twenty-zero"
	3, // one
	3, // two
	5, // three
	4, // four
	4, // five
	3, // six
	5, // seven
	5, // eight
	4, // nine
	3, // ten
	6, // eleven
	6, // twelve
	8, // thirteen
	8, // fourteen
	7, // fifteen
	7, // sixteen
	9, // seventeen
	8, // eighteen
	8, // nineteen
};

static unsigned multiples_of_ten[10] = {
	0, // zero
	0, // ten; anything below 20 is handled by small_numbers
	6, // twenty
	6, // thirty
	5, // forty
	5, // fifty
	5, // sixty
	7, // seventy
	6, // eighty
	6, // ninety
};

unsigned letters_in_english(unsigned num){
	assert(num < 1000000);
	unsigned total = 0;
	unsigned orig = num;
	if (num >= 1000){
		total += letters_in_english(num / 1000) + LEN_THOUSAND;
	}
	num %= 1000;
	
	if (num >= 100){
		total += small_numbers[num / 100] + LEN_HUNDRED;
	}
	num %= 100;
	
	if (orig > 100 && num != 0){
		total += LEN_AND;
	}
	
	if (num >= 20){
		total += multiples_of_ten[num / 10] + small_numbers[num % 10];
	} else {
		total += small_numbers[num];
	}
	return total;
}

unsigned sum_letters_one_to(unsigned n){
	unsigned sum = 0;
	for (unsigned i = 1; i <= n; i++){
		sum += letters_in_english(i);
	}
	return sum;
}

int main(){
	assert(sum_letters_one_to(  5) == 19);
	assert(letters_in_english( 42) ==  8);
	assert(letters_in_english(342) == 23);
	assert(letters_in_english(115) == 20);
	printf("%u\n", sum_letters_one_to(1000));
	return 0;
}