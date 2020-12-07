#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
      int min_row{0};
      int max_row{127};
      int row{0};
      int min_col{0};
      int max_col{7};
      int col{0};
      for (auto pos : line)
      {
        if (pos == 'F')
        {
          if (max_row == min_row + 1)
            row = min_row;
          else
            max_row = (min_row + max_row) / 2;
        }
        else if (pos == 'B')
        {
          if (max_row == min_row + 1)
            row = max_row;
          else
            min_row = (min_row + max_row) / 2 + 1;
        }
        else if (pos == 'R')
        {
          if (max_col == min_col + 1)
            col = max_col;
          else
            min_col = (min_col + max_col) / 2 + 1;
        }
        else if (pos == 'L')
        {
          if (max_col == min_col + 1)
            col = min_col;
          else
            max_col = (min_col + max_col) / 2;
        }
      }
      int seat_id = row * 8 + col;
      m_seat_list.push_back(seat_id);
      if (max_seat_id < seat_id)
        max_seat_id = seat_id;
    }
  }

  auto solve_a() const -> int;
  auto solve_b() -> int;
  std::vector<int> m_seat_list;
  int max_seat_id{0};
};

auto Solution::solve_a() const -> int
{
  return max_seat_id;
}

auto Solution::solve_b() -> int
{
  std::sort(m_seat_list.begin(), m_seat_list.end(), std::greater<int>());
  int pre = m_seat_list[0] + 1;
  for (auto item : m_seat_list)
  {
    if (item != pre - 1)
      return pre - 1;
    pre = item;
  }
  return -1;
}

auto main() -> int
{
  Solution day5{"../day5/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day5.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day5.solve_b() << std::endl;
  return 0;
}