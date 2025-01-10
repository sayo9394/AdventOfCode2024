#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <numeric>
#include <map>

// This function reads a file where each line is in the form of a number <space>
// number
std::optional<std::pair<std::multiset<int>, std::multiset<int>>>
read_file(const std::string& filename)
{
    std::multiset<int> left_list;
    std::multiset<int> right_list;

    auto file = std::ifstream(filename);
    if (!file.is_open())
    {
        return std::nullopt;
    }

    std::string line;
    while (std::getline(file, line))
    {
        int left_number;
        int right_number;
        // lets use iostream to parse the line instead of sscanf
        std::istringstream iss(line);
        if (!(iss >> left_number >> right_number))
        {
            std::cout << "Error reading file\n";
            return std::nullopt;
        }
        left_list.insert(left_number);
        right_list.insert(right_number);
        std::cout << "Left: " << left_number << " Right: " << right_number << '\n';
    }

    std::cout << "Left list size: " << left_list.size() << '\n';
    std::cout << "Right list size: " << right_list.size() << '\n';

    return std::make_pair(left_list, right_list);
}

// This is part 1 of day 1
// This function calculates the difference between two sets into a vector
// the function then returns the sum of the elements in the vector
std::optional<int> calculate_set_difference(const std::multiset<int>& left,
                                            const std::multiset<int>& right)
{
    std::vector<int> difference;
    // check that the sizes of the two sets are the same
    if (left.size() != right.size())
    {
        std::cout << "The sizes of the two sets are not the same\n";
        return std::nullopt;
    }
    // return the sum of the elements in the vector
    std::transform(left.begin(), left.end(), right.begin(), std::back_inserter(difference),
                   [](int a, int b) { return std::abs(a - b); });
    return std::make_optional(std::accumulate(difference.begin(), difference.end(), 0));
}

// Part 2 of day 1
// This function calculates the total similarity score. The similarity score is by adding up each
// number in the left list after multipluying it by the number of times it appears in the right list
std::optional<int> calculate_frequency_weighted_sum(const std::multiset<int>& left,
                                                    const std::multiset<int>& right)
{
    int weighted_sum = 0;
    for (const auto& number : left)
    {
        weighted_sum += number * right.count(number); // Direct count on the multiset
        std::cout << "Number: " << number << " Frequency: " << right.count(number) << '\n';
    }
    return weighted_sum;
}

// the file name is sent as an argument to the program
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    const auto file_name = argv[1];
    std::cout << "Hello, World!\n";
    const auto result = read_file(std::string(file_name));
    if (!result.has_value())
    {
        std::cerr << "Error reading file\n";
        return 1;
    }

    const auto difference = calculate_set_difference(result.value().first, result.value().second);
    if (!difference.has_value())
    {
        std::cerr << "Error calculating set difference\n";
        return 1;
    }
    std::cout << "The sum of the differences is: " << difference.value() << '\n';

    const auto similarity_score =
            calculate_frequency_weighted_sum(result.value().first, result.value().second);
    if (!similarity_score.has_value())
    {
        std::cerr << "Error calculating similarity score\n";
        return 1;
    }
    std::cout << "The similarity score is: " << similarity_score.value() << '\n';

    return 0;
}
