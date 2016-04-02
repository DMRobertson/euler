struct Fibonacci {
    last: u32,
    current: u32
}

impl Fibonacci {
    fn new() -> Self {
        Fibonacci {
            last: 0,
            current: 1
        }
    }
}

impl Iterator for Fibonacci {
    type Item = u32;

    fn next(&mut self) -> Option<u32> {
        let temp = self.last;
        self.last = self.current;
        self.current = self.last + temp;
        Some(self.current)
    }
}

fn sum_upto(summands: Fibonacci, max: u32) -> u32 {
    let mut sum = 0;
    for summand in summands {
        if summand >= max {
            break;
        }
        if summand % 2 == 0 && summand < max {
            sum += summand;
        }
    }
	sum
}

fn main() {
	let generator = Fibonacci::new();
    let sum = sum_upto(generator, 4_000_000);
	println!("{}", sum);
}
