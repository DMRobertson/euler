#include <stdio.h>
#include <assert.h>

/*
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

unsigned long choose(unsigned long options, unsigned long choices){
	//See http://blog.plover.com/math/choose-2.html
	unsigned long out = 1;
	if (choices > options){
		return 0;
	}
	for (unsigned long divisor = 1; divisor <= choices; divisor++){
		out *= options;
		options--;
		out /= divisor;
	}
	return out;
}

unsigned long num_paths(unsigned long width, unsigned long height){
	return choose(width + height, width);
}

int main(){
	assert(num_paths(2, 2) == 6);
	printf("%lu\n", num_paths(20, 20));
	return 0;
}