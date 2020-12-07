#include <fstream>
#include <iostream>
#include <queue>
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
    while (std::getline(input, line))
    {
      m_input_queue.push(line);
    }
  }

  int helper(int right, int down) const;
  int solve_a() const;
  uint64_t solve_b() const;
  std::queue<std::string> m_input_queue;
};

int Solution::helper(int right, int down) const
{
  std::queue<std::string> queen{m_input_queue};
  int current_index = 0;
  int tree_count = 0;
  while (!queen.empty())
  {
    std::string row = queen.front();
    if (current_index != 0)
    {
      while (row.size() <= current_index)
      {
        row += row;
      }
      if (row[current_index] == '#')
        ++tree_count;
    }
    current_index += right;
    for (int i = 0; i < down; ++i)
    {
      if (!queen.empty())
        queen.pop();
    }
  }

  return tree_count;
}

int Solution::solve_a() const
{
  return helper(3, 1);
}

uint64_t Solution::solve_b() const
{
  return helper(1, 1) * helper(3, 1) * helper(5, 1) * helper(7, 1) * helper(1, 2);
}

int main()
{
  Solution day3{"../day3/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day3.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day3.solve_b() << std::endl;
  return 0;
}