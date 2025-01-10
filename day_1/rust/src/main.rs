// reads a file into 2 sets
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

// read the file line by line, where each line is a number space number
// return 2 vectors of int
// each string is a line in the file
// if there is an error, returning 2 empty vectors
fn read_lines<P>(filename: P) -> Result<(Vec<i32>, Vec<i32>), Box<dyn std::error::Error>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename).unwrap();
    let lines = io::BufReader::new(file).lines();
    let mut set1 = Vec::new();
    let mut set2 = Vec::new();

    for line in lines {
        let line = line.unwrap();
        let mut iter = line.split_whitespace();

        let num1_str = iter.next().ok_or("Missing first number")?;
        let num1 = num1_str
            .parse::<i32>()
            .map_err(|_| "Invalid first number format")?;

        let num2_str = iter.next().ok_or("Missing second number")?;
        let num2 = num2_str
            .parse::<i32>()
            .map_err(|_| "Invalid second number format")?;

        set1.push(num1);
        set2.push(num2);
    }

    Ok((set1, set2))
}

// part 2
// This function calculates the total similarity score. The similarity score is by adding up each
// number in the left list after multipluying it by the number of times it appears in the right list
fn calculate_frequency_weighted_sum(set1: Vec<i32>, set2: Vec<i32>) -> i32 {
    let mut sum = 0;
    for num in set1 {
        let count = set2.iter().filter(|&n| *n == num).count() as i32;
        sum += num * count;
    }
    sum
}

fn main() {
    println!("Hello, world!");
    // we need to read to read the file in /intput/input.txt
    // get file from args
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <filename>", args[0]);
        std::process::exit(1);
    }
    let filename = &args[1];
    // let (mut set1, mut set2) = read_lines(filename);
    match read_lines(filename) {
        Ok((mut set1, mut set2)) => {
            set1.sort();
            set2.sort();

            let difference = set1
                .iter()
                .zip(set2.iter())
                .map(|(a, b)| (a - b).abs())
                .collect::<Vec<i32>>();

            let sum = difference.iter().sum::<i32>();

            println!("{:?}", sum);

            let frequency_weighted_sum = calculate_frequency_weighted_sum(set1, set2);
            println!("{:?}", frequency_weighted_sum);
        }
        Err(e) => {
            eprintln!("Error: {}", e);
            std::process::exit(1);
        }
    }
}
