#ifndef COMPARE_
#define COMPARE_

#include <stdlib.h>

int cmp_unsigned(const void* a, const void* b){
	unsigned A = *(unsigned*) a;
	unsigned B = *(unsigned*) b;
	return (A > B) - (B > A) ;
}

int cmp_size_t(const void* a, const void* b){
	size_t A = *(size_t*) a;
	size_t B = *(size_t*) b;
	return (A > B) - (B > A);
}

#endif //COMPARE_