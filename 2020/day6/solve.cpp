#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Solution
{
  public:
  explicit Solution(const std::string &file_path)
  {
    std::ifstream input{file_path, std::ios::binary};
    if (input.fail())
    {
      std::cout << "Error opening " << file_path;
    }
    std::string line;
    int member_count{0};
    std::map<char, int> questions;
    while (std::getline(input, line))
    {
      if (line.empty())
      {
        yes_count += questions.size();
        for (auto item : questions)
        {
          if (item.second == member_count)
            ++same_yes_count;
        }
        questions.clear();
        member_count = 0;
        continue;
      }

      for (auto q : line)
      {
        ++questions[q];
      }

      ++member_count;
    }
  }

  auto solve_a() const -> int;
  auto solve_b() const -> int;
  int yes_count{0};
  int same_yes_count{0};
};

auto Solution::solve_a() const -> int
{
  return yes_count;
}

auto Solution::solve_b() const -> int
{
  return same_yes_count;
}

auto main() -> int
{
  Solution day6{"../day6/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day6.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day6.solve_b() << std::endl;
  return 0;
}