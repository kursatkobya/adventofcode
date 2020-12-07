#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
  explicit Solution(const std::string& file_path) : m_input_{file_path, std::ios::binary}
  {
    if (m_input_.fail())
    {
      std::cout << "Error opening " << file_path;
    }
    std::string line;
    while (std::getline(m_input_, line))
    {
      Pwd item;
      std::uint32_t start_pos = 0;
      std::uint32_t end_pos = line.find('-');
      std::string min = line.substr(start_pos, end_pos);
      item.min = std::stoi(min);
      start_pos = end_pos + 1;
      end_pos = line.find(' ', start_pos);
      std::string max = line.substr(start_pos, end_pos - start_pos);
      item.max = std::stoi(max);
      start_pos = end_pos + 1;
      end_pos = line.find(' ', start_pos);
      std::string character = line.substr(start_pos, end_pos - start_pos);
      item.key = character[0];
      start_pos = end_pos + 1;
      end_pos = line.size();
      item.password = line.substr(start_pos, end_pos - start_pos);
      m_input_vector_.push_back(item);
    }
  }

  int solve_a() const;
  int solve_b();
  class Pwd
  {
    public:
    int min = 0;
    int max = 0;
    char key;
    std::string password;
  };  

  private:
  std::ifstream m_input_;
  std::vector<Pwd> m_input_vector_;
};

int Solution::solve_a() const
{
  int valid_pwd = 0;
  std::vector<Pwd> test_vec = m_input_vector_;
  while (!test_vec.empty())
  {
    Pwd item = test_vec.back();
    int count = 0;
    for (int i = 0; i < item.password.size(); ++i)
    {
      if (item.password[i] == item.key)
        ++count;
    }
    if (item.min <= count && count <= item.max)
      ++valid_pwd;
    test_vec.pop_back();
  }

  return valid_pwd;
}

int Solution::solve_b()
{
  int valid_pwd = 0;
  while (!m_input_vector_.empty())
  {
    Pwd item = m_input_vector_.back();
    bool min_exist = false;
    bool max_exist = false;
    if (item.password[item.min - 1] == item.key)
      min_exist = true;
    if (item.password[item.max - 1] == item.key)
      max_exist = true;
    if (min_exist xor max_exist)
      ++valid_pwd;
    m_input_vector_.pop_back();
  }

  return valid_pwd;
}

int main()
{
  Solution day2{"../day2/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day2.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day2.solve_b() << std::endl;
  return 0;
}