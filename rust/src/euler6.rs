use std::ops::Add;

fn sum_square_difference(start: u32, end: u32) -> u32 {
	let sum_squared = (start..end).fold(0, Add::add).pow(2);
	let sum_squares = (start..end).map(|x| x * x)
		.fold(0, Add::add);
	sum_squared - sum_squares
}

/// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
fn main() {
	println!("{}", sum_square_difference(1, 101));
}

/// The sum of the squares of the first ten natural numbers is,
/// 	12 + 22 + ... + 102 = 385
/// The square of the sum of the first ten natural numbers is,
/// 	(1 + 2 + ... + 10)2 = 552 = 3025
/// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
#[test]
fn test() {
	let expected = 2640;
	let result = sum_square_difference(1, 11);
	assert_eq!(result, expected);
}