mod numthry;
use numthry::Primes;

/// What is the 10 001st prime number?
fn main() {
	// note that the first item is .nth(0)
	println!("{}", Primes::new().nth(10_001 - 1).unwrap());
}

/// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
#[test]
fn test() {
	let expected = vec![2, 3, 5, 7, 11, 13];
	let result: Vec<u64> = Primes::new().take(6).collect();
	assert_eq!(result, expected);
}
