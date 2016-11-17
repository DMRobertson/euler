//The method of squares, from http://stackoverflow.com/a/101613/5252017
int powi(int base, int exp){
	int result = 1;
	while (exp){
		if (exp & 1){
			result *= base;
		}
		exp >>= 1;
		base *= base;
	}
	return result;
}