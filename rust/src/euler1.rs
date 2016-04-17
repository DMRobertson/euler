/// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
/// The sum of these multiples is 23.

#[test]
fn test() {
	let expected = 23;
	let result = sum_multiples_3_5(1, 10);
    assert_eq!(result, expected);
}


fn sum_multiples_3_5 (start: u32, end: u32) -> u32 {
    let mut sum = 0;
    for i in start..end {
        if i % 3 == 0 || i % 5 == 0 {
            sum += i;
        }
    }
    sum
}

/// Find the sum of all the multiples of 3 or 5 below 1000.
pub fn main() {
    println!("{}", sum_multiples_3_5(1, 1000));
}

