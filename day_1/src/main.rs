// reads a file into 2 sets
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

// read the file line by line, where each line is a number space number
// return 2 vectors of int
// each string is a line in the file
// if there is an error, returning 2 empty vectors
fn read_lines<P>(filename: P) -> (Vec<i32>, Vec<i32>)
where P: AsRef<Path>, {
    let file = File::open(filename).unwrap();
    let lines = io::BufReader::new(file).lines();
    let mut set1 = Vec::new();
    let mut set2 = Vec::new();
    for line in lines {
        let line = line.unwrap();
        let mut iter = line.split_whitespace();
        let num1 = iter.next().unwrap().parse::<i32>().unwrap();
        let num2 = iter.next().unwrap().parse::<i32>().unwrap();
        set1.push(num1);
        set2.push(num2);
    }
    (set1, set2)
}


fn main() {
    println!("Hello, world!");
    // we need to read to read the file in /intput/input.txt 
    let (mut set1, mut set2) = read_lines("input/input.txt");
    set1.sort();
    set2.sort();

    let difference = set1.iter()
        .zip(set2.iter())
        .map(|(a, b)| (a - b).abs())
        .collect::<Vec<i32>>();

    let sum = difference.iter().sum::<i32>();

    println!("{:?}", sum);
}
