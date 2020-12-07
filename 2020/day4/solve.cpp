#include <fstream>
#include <iostream>
#include <map>
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
    Passport current_passport;
    std::string key;
    std::string value;
    while (std::getline(input, line, '\n'))
    {
      if (line.empty())
      {
        m_passport_list.push_back(current_passport);
        current_passport.clear();
        continue;
      }
      std::size_t start_pos = 0;
      while (start_pos != std::string::npos)
      {
        start_pos = line.find(':');
        key = line.substr(0, start_pos);
        line.erase(0, start_pos + 1);
        if ((start_pos = line.find(' ')) != std::string::npos)
        {
          value = line.substr(0, start_pos);
          line.erase(0, start_pos + 1);
        }
        else
        {
          value = line;
          start_pos = std::string::npos;
        }
        current_passport[key] = value;
      }
    }
  }

  using Passport = std::map<std::string, std::string>;

  static auto is_pass_port_valid(Passport pass) -> bool
  {
    std::vector<std::string> required_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    for (const auto &item : required_fields)
    {
      if (pass.find(item) == pass.end())
      {
        return false;
      }
    }
    return true;
  }

  static auto is_pass_port_really_valid(Passport pass) -> bool
  {
    try
    {
      std::vector<std::string> required_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
      int byr = std::stoi(pass["byr"]);
      if (byr > 2002 || byr < 1920)
      {
        return false;
      }

      int iyr = std::stoi(pass["iyr"]);
      if (iyr > 2020 || iyr < 2010)
      {
        return false;
      }

      int eyr = std::stoi(pass["eyr"]);
      if (eyr > 2030 || eyr < 2020)
      {
        return false;
      }

      std::string hgts = pass["hgt"];
      std::string unit = hgts.substr(hgts.size() - 2);
      int hgt = std::stoi(hgts.substr(0, hgts.size() - 2));
      if (unit == "cm")
      {
        if (hgt < 150 || hgt > 193)
          return false;
      }
      else if (unit == "in")
      {
        if (hgt < 59 || hgt > 76)
          return false;
      }
      else
      {
        return false;
      }
      std::string hcl = pass["hcl"];
      if (hcl[0] != '#')
      {
        return false;
      }

      for (char ch : hcl.substr(1))
      {
        if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f'))
        {
          continue;
        }
                  return false;
      }

      std::vector<std::string> valid_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
      bool valid{false};
      for (const auto &color : valid_colors)
      {
        if (pass["ecl"] == color)
          valid = true;
      }
      if (!valid)
        return false;

      std::string pid = pass["pid"];
      if (pid.size() != 9)
        return false;

      for (char ch : pid)
      {
        if (!(ch >= '0' && ch <= '9'))
          return false;
      }
    }
    catch (std::exception &e)
    {
      return false;
    }
    return true;
  }

  auto solve_a() -> int;
  auto solve_b() -> int;
  std::vector<Passport> m_passport_list;
};

auto Solution::solve_a() -> int
{
  int count{0};
  for (const auto &item : m_passport_list)
  {
    if (is_pass_port_valid(item))
      ++count;
  }
  return count;
}

auto Solution::solve_b() -> int
{
  int count{0};
  for (const auto &item : m_passport_list)
  {
    if (is_pass_port_really_valid(item))
      ++count;
  }
  return count;
}

auto main() -> int
{
  Solution day4{"../day4/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day4.solve_a() << std::endl;
  std::cout << "Part B" << std::endl;
  std::cout << day4.solve_b() << std::endl;
  return 0;
}