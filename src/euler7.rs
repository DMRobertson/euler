fn is_prime(n: u32) -> bool {
	let bound = (n as f32).sqrt() as u32;
	for i in 2..bound+1 {
		if n % i == 0 {
			return false
		}
	}
	true
}

struct Primes {
		candidate: u32
}

impl Primes {
	fn new() -> Primes {
		Primes{ candidate: 0 }
	}
}

impl Iterator for Primes {
	type Item = u32;

	fn next(&mut self) -> Option<u32> {
		if self.candidate < 1 {
			self.candidate = 1;
			Some(2)
		} else {
			self.candidate += 2;
			while !is_prime(self.candidate) {
				self.candidate += 2;
			}
			Some(self.candidate)
		}
	}
}

/// What is the 10 001st prime number?
fn main() {
	// note that the first item is .nth(0)
	println!("{}", Primes::new().nth(10_001 - 1).unwrap());
}

/// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
#[test]
fn test() {
	let expected = vec![2, 3, 5, 7, 11, 13];
	let result: Vec<u32> = Primes::new().take(6).collect();
	assert_eq!(result, expected);
}
