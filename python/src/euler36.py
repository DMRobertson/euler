"""The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)"""

def is_palindrome(str):
	return all(
		str[i] == str[-i-1] for i in range(len(str) // 2)
	)

def is_binary_decimal_palindrome(x):
	dec = "{0:d}".format(x)	
	bin = "{0:b}".format(x)
	return is_palindrome(dec) and is_palindrome(bin)
	

if __name__ == "__main__":
	print(
		sum( (x, print(x))[0] for x in range(1, 1000000) if is_binary_decimal_palindrome(x) )
	)