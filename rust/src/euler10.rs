mod numthry;
use numthry::Primes;

fn sum_primes_below(limit: u64) -> u64 {
	Primes::new()
		.take_while(|&x| x < limit)
		.fold(0, |acc, x| acc + x)
}

/// Find the sum of all the primes below two million.
fn main() {
	println!("{}", sum_primes_below(2_000_000));
}

/// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
#[test]
fn test() {
	let expected = 17;
	let result = sum_primes_below(10);
	assert_eq!(result, expected);
}
