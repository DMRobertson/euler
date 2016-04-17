use std::cmp::min;

fn is_pythagorean_triplet(a: u32, b: u32, c: u32) -> bool {
	a*a + b*b == c*c
}

/// Compute the ceiling of u/d, without casting to floats.
fn ceil(n: u32, d: u32) -> u32 {
	(n + d - 1)/d
}

/// Enumerate triples 1a <= b <= c for which a + b + c = sum.
fn pythag_triplet_sum(sum: u32) -> Option<[u32; 3]> {
	// We'll try to do it efficiently.
	let mut triplet = None;
	// Start with the largest: c.
	// It must be at least ceil(sum/3),
	// and at most sum - 2.
	let lower_c = ceil(2, 3);
	// Like Python, ranges are closed on the left and open at the top.
	let upper_c = sum + 1 - 2;
	for c in lower_c..upper_c{
		// Next choose b.
		// It must be at most c, and at most sum - c - 1,
		// and must be at least ceil((sum - c)/2)
		let lower_b = ceil(sum - c, 2);
		let upper_b = min(c + 1, sum - c);
		for b in lower_b..upper_b {
			let a = sum - c - b;
			if is_pythagorean_triplet(a, b, c){
				triplet = Some([a, b, c]);
				break;
			}
		}
	}
	triplet
}

/// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
/// Find the product abc.
fn main() {
	let triplet = pythag_triplet_sum(1000).unwrap();
	println!("{}", triplet.iter().fold(1, |acc, &x| acc * x));
}

/// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
/// 	a^2 + b^2 = c^2
/// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
#[test]
fn test() {
	let expected = true;
	let result = is_pythagorean_triplet(3, 4, 5);
	assert_eq!(result, expected);
}

#[test]
fn test_ceil() {
	assert_eq!(ceil(0, 5), 0);
	assert_eq!(ceil(1, 5), 1);
	assert_eq!(ceil(2, 5), 1);
	assert_eq!(ceil(3, 5), 1);
	assert_eq!(ceil(4, 5), 1);
	assert_eq!(ceil(5, 5), 1);
}
