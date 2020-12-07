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
    std::string str;
    while (std::getline(m_input_, str))
    {
      m_input_vector_.push_back(std::stoi(str));
    }
  }

  int solve_a();
  int solve_b();

  private:
  std::ifstream m_input_;
  std::vector<int> m_input_vector_;
};

int Solution::solve_a()
{
  std::string str;
  for (int i = 0; i < m_input_vector_.size() - 1; ++i)
  {
    for (int j = i + 1; j < m_input_vector_.size(); ++j)
    {
      if (m_input_vector_[i] + m_input_vector_[j] == 2020)
      {
        return m_input_vector_[i] * m_input_vector_[j];
      }
    }
  }

  return 0;
}

int Solution::solve_b()
{
  std::string str;
  for (int i = 0; i < m_input_vector_.size() - 2; ++i)
  {
    for (int j = i + 1; j < m_input_vector_.size() - 1; ++j)
    {
      for (int k = j + 1; k < m_input_vector_.size(); ++k)
      {
        if (m_input_vector_[i] + m_input_vector_[j] + m_input_vector_[k] == 2020)
        {
          return m_input_vector_[i] * m_input_vector_[j] * m_input_vector_[k];
        }
      }
    }
  }

  return 0;
}

int main()
{
  Solution day1{"../day1/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day1.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day1.solve_b() << std::endl;

  return 0;
}