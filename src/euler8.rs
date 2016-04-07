use std::io::{BufRead, BufReader};
use std::fs::File;
use std::cmp::max;

const ASCII_NEWLINE: u8 = 0xa;

fn product ( digits: &[u8] ) -> u64 {
	digits.iter().fold(1, |acc, &x| acc * (x as u64))
}

fn load_digits( filepath: & str ) -> Vec<u8> {
	let f = File::open(filepath).unwrap();
	let mut reader = BufReader::new(f);
	let mut output = Vec::new();
	reader.read_until(ASCII_NEWLINE, &mut output).unwrap();

	if output[output.len() - 1] == ASCII_NEWLINE {
		output.pop();
	}

	// assume that the file is encoded in something ascii compatible.
	// Then the character '0' is encoded as 0x30, so we should subtract this to get the actual number.
	for index in 0..output.len() {
		output[index] -= 0x30;
	}
	output
}

fn max_product_of_substring(digits: Vec<u8>, width: usize) -> u64 {
	if width > digits.len() {
		panic!("Not enough digits to find a product of length {}", width);
	};
	let mut max_product = 0;
	for index in 0..digits.len()-width {
		max_product = max(max_product, product(&digits[index..index+width]));
	}
	max_product
}

/// Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?
fn main() {
	let digits = load_digits("resource/problem8.num");
	println!("{}", max_product_of_substring(digits, 13) );
}

/// The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.
#[test]
fn test() {
	let expected = 5832;
	let digits = load_digits("resource/problem8.num");
	let result = max_product_of_substring(digits, 4);
	assert_eq!(result, expected);
}

#[test]
fn test_product() {
	let expected = 24;
	let digits = vec![1, 2, 3, 4];
	let result = product(&digits);
	assert_eq!(result, expected);
}
