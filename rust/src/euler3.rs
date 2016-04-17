/// The prime factors of 13195 are 5, 7, 13 and 29.

#[test]
fn test(){
	let expected = vec![5, 7, 13, 29];
	let result = prime_factors(13195);
	assert_eq!(result, expected);
}

fn prime_factors(mut n: u64) -> Vec<u64> {
	let mut factors = Vec::new();
	let mut trial_divisor = 2;
	loop {
		if n % trial_divisor == 0 {
			factors.push(trial_divisor);
			n /= trial_divisor;
			if n == 1 {
				break
			}
		} else {
			trial_divisor += 1;
		}
	}
	factors
}

/// The prime factors of 13195 are 5, 7, 13 and 29.

fn main() {
	let factors = prime_factors(600851475143);
	let max_factor = factors.last().unwrap();
	println!("{}", max_factor);
}
