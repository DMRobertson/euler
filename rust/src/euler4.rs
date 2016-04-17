use std::cmp::max;

fn length ( n: u32, base: u32) -> u32 {
	let mut length = 0;
	let mut compare = 1;
	loop {
		if compare > n {
			break;
		}
		length += 1;
		compare *= base;
	}
	length
}

fn is_palindrome (n: u32, base: u32) -> bool {
	let len = length(n, base);
	let mid = (len + 1) / 2;
	for i in 0..mid {
		let upper = (n / base.pow(len - i - 1)) % base;
		let lower = (n / base.pow(i)      ) % base;
		if upper != lower {
			return false
		}
	}
	true
}

fn max_palindromic_product ( start: u32, end: u32) -> u32 {
	let mut previous_best = 0;
	for x in start..end {
		for y in start..end {
			let product = x * y;
			if is_palindrome(product, 10) {
				previous_best = max(product, previous_best);
			}
		}
	}
	previous_best
}

/// Find the largest palindrome made from the product of two 3-digit numbers.
fn main() {
	println!("{}", max_palindromic_product(100, 1000));
}

/// A palindromic number reads the same both ways.
/// The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
#[test]
fn test() {
	let expected = 9009;
	let result = max_palindromic_product(10, 100);
	assert_eq!(result, expected);
}