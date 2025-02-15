// Creator: Simon Ayoub
// Date: 2025-02-10
// Day 2 of Advent of Code 2024
// Red-Nosed Report - https://adventofcode.com/2024/day/2

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

/*
 * the function read_line will take a filesystem path as input.
 * each line in the file will be a list of numbers separated by a space.
 * each number is called a level, and each line is called a report.
 * the function will return a vector of vectors of integers.
 */
std::optional<std::vector<std::vector<int>>> read_lines(const std::string_view file_name)
{
    // open the file
    const auto file = std::filesystem::path { file_name };
    if (!std::filesystem::exists(file))
    {
        std::cerr << "Error: " << file << " does not exist.\n";
        return std::nullopt;
    }

    std::ifstream input { file };
    if (!input)
    {
        std::cerr << "Error: cannot open " << file << ".\n";
        return std::nullopt;
    }

    // read the lines
    std::vector<std::vector<int>> lines;
    for (std::string line; std::getline(input, line);)
    {
        std::vector<int> levels;
        std::istringstream iss { line };
        for (int level; iss >> level;)
        {
            levels.push_back(level);
        }
        lines.push_back(levels);
    }

    return lines;
}


// a report is safe is one that has both of the following are true:
// - the levels are either all increasing or all decreasing
// - any two adjacent levels differ by at least 1 and at most 3
bool is_safe_report(const std::vector<int>& report)
{
    // check whether the report is safe
    bool increasing = true;
    bool decreasing = true;
    bool safe_diff = true;

    for (size_t i = 1; i < report.size(); ++i)
    {
        if (report[i] > report[i-1])
        {
            decreasing = false;
        }
        else if (report[i] < report[i-1])
        {
            increasing = false;
        }
        // check the absolute difference between two adjacent levels
        // if the difference is at least 1 and at most 3, then the report is safe
        if (std::abs(report[i] - report[i-1]) < 1 || std::abs(report[i] - report[i-1]) > 3)
        {
            safe_diff = false;
        }
    }
    return (increasing || decreasing) && safe_diff;
}

int main(int argc, char* argv[])
{
    // get the name of the input file from command line
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    const auto input_file = std::filesystem::path { argv[1] };
    if (!std::filesystem::exists(input_file))
    {
        std::cerr << "Error: " << input_file << " does not exist.\n";
        return 2;
    }

    const auto lines = read_lines(input_file.string());
    if (lines)
    {
        int safe_reports = 0;
        std::cout << "Number of reports: " << lines->size() << '\n';
        // check whether the reports are safe
        for (const auto& report : *lines)
        {
            std::cout << "Number of levels: " << report.size() << '\n';
             std::cout << "Is the report safe? " << std::boolalpha << is_safe_report(report) << '\n';
            if (is_safe_report(report))
            {
                ++safe_reports;
            }
        }
        std::cout << "Number of safe reports: " << safe_reports << '\n';
    }
    else
    {
        std::cerr << "Error: cannot read the lines.\n";
        return 3;
    }

    return 0;
}
