/// Functions related to number theory

fn is_prime(n: u64) -> bool {
	let bound = (n as f32).sqrt() as u64;
	for i in 2..bound+1 {
		if n % i == 0 {
			return false
		}
	}
	true
}

pub struct Primes {
		candidate: u64
}

impl Primes {
	pub fn new() -> Primes {
		Primes{ candidate: 0 }
	}
}

impl Iterator for Primes {
	type Item = u64;

	fn next(&mut self) -> Option<u64> {
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
