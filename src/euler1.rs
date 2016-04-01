fn sum_multiples_3_5 (start: u32, end: u32) -> u32 {
    let mut sum = 0;
    for i in start..end {
        if i % 3 == 0 || i % 5 == 0 {
            sum += i
        }
    }
    sum
}

pub fn main() {
    println!("{}", sum_multiples_3_5(1, 1000))
}

#[test]
fn test() {
    assert_eq!(23, sum_multiples_3_5(1, 10))
}
