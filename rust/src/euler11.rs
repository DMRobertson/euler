use std::io::{BufRead, BufReader};
use std::fs::File;

struct IntReader {
	reader: &BufReader,
	buffer: Vec<u8>
}

impl IntReader {
	fn new(filepath: &str) -> IntReader {
		let f = File::open(filepath).unwrap();
		IntReader {
			reader: BufReader::new(f),
			buffer: Vec::new()
		}
	}
}

impl Iterator for IntReader {
	type Item = u8;
	fn next(&mut self) -> Option<u8> {
		None
	}
}

/// In the 20×20 grid below, four numbers along a diagonal line have been marked in red.
/// The product of these numbers is 26 × 63 × 78 × 14 = 1788696.
/// What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?
const SIZE: usize = 20;
fn main() {
	let mut grid : [u8; SIZE * SIZE] = [false; SIZE * SIZE];

	println!("{}", grid[0]);
}
