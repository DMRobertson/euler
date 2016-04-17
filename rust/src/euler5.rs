use std::ops::Range;

fn lcm(numbers: Range<u32>) -> u32 {
	let mut iter = numbers.into_iter();
	let mut lcm = iter.next().unwrap();
	for number in iter {
		lcm = lcm_pair(lcm, number);
	}
	lcm
}

fn lcm_pair(a: u32, b: u32) -> u32 {
	(a * b) / gcd_pair(a, b)
}

fn gcd_pair(mut a: u32, mut b: u32) -> u32 {
	loop {
		if b == 0 {
			break;
		}
		let temp = b;
		b = a % b;
		a = temp;
	}
	a
}

/// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
fn main() {
	println!("{}", lcm(1..20));
}

/// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
#[test]
fn test() {
	let expected = 2520;
	let result = lcm(1..10);
	assert_eq!(result, expected);
}