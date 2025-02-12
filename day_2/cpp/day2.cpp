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

    return 0;
}
