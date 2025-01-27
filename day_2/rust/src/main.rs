// Day 2 of Advent of Code 2024
// Red-Nosed Reports - https://adventofcode.com/2024/day/2

use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

// Read the input file. Each line in the line is called a report, which consits of a list of
// numbers. The numbers are called levels that are separated by spaces.
// eg:
// 7 6 4 2 1
// 1 2 7 8 9
// 9 7 6 2 1
// 1 3 2 4 5
// 8 6 4 4 1
// 1 3 6 7 9
// This example data contains six reports each containing five levels.

fn read_lines<P>(filename: P) -> Result<Vec<Vec<i32>>, Box<dyn std::error::Error>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    let lines = io::BufReader::new(file).lines();
    let mut reports = Vec::new();

    for line in lines {
        let line = line.unwrap();
        let mut levels = Vec::new();
        for num_str in line.split_whitespace() {
            let num = num_str
                .parse::<i32>()
                .map_err(|_| "Invalid number format")?;
            levels.push(num);
        }
        reports.push(levels);
    }

    Ok(reports)
}

// calculate if the report is safe
// A safe report is one that has both of the following are true:
// - The levels are either all increasing or all decreasing
// - Any two adjacent levels differ by atleast one and at most 3
fn is_safe_report(report: &Vec<i32>) -> bool {
    let mut is_increasing = true;
    let mut is_decreasing = true;

    for i in 1..report.len() {
        let new_diff = report[i] - report[i - 1];
        if new_diff.abs() < 1 || new_diff.abs() > 3 {
            return false;
        }

        if new_diff > 0 {
            is_decreasing = false;
        } else if new_diff < 0 {
            is_increasing = false;
        }
    }

    return is_increasing || is_decreasing;
}

fn main() {
    println!("Hello, world!");
    match read_lines("../input/input.txt") {
        Ok(reports) => {
            // return the number of safe reports
            let safe_reports = reports.iter().filter(|r| is_safe_report(r)).count();
            println!("Number of safe reports: {}", safe_reports);
        }
        Err(e) => {
            eprintln!("Error: {}", e);
        }
    }
}
