#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Bag
{
  public:
  Bag(int c, std::string n) : name{std::move(n)}, count{c}
  {
  }
  std::string name;
  int count;
};

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
      std::string::size_type pos = line.find(" bags ");
      std::string rulename = line.substr(0, pos);
      std::string garbage_chars{" bags contain "};
      line.erase(0, pos + garbage_chars.size());
      std::vector<Bag> bag_list;
      while ((pos = line.find(", ")) != std::string::npos)
      {
        std::string unparsed_bag{line.substr(0, pos)};
        auto mid_pos = unparsed_bag.find(" bag");
        Bag el{std::stoi(unparsed_bag.substr(0, 1)), unparsed_bag.substr(2, mid_pos - 2)};
        bag_list.push_back(el);
        line.erase(0, pos + 2);
      }
      try
      {
        std::string unparsed_bag{line.substr(0, pos)};
        auto mid_pos = unparsed_bag.find(" bag");
        Bag el{std::stoi(unparsed_bag.substr(0, 1)), unparsed_bag.substr(2, mid_pos - 2)};
        bag_list.push_back(el);
      }
      catch (std::invalid_argument &e)
      {
        std::cout << "no other bags" << std::endl;
      }
      rules[rulename] = bag_list;
    }
    rules.erase("shiny gold");
  }

  auto solve_a() const -> int;
  static auto solve_b() -> int;
  int yes_count{0};
  int same_yes_count{0};
  std::unordered_map<std::string, std::vector<Bag>> rules;
  std::vector<std::string> has_shiny;
};

bool search_inner_bags(const std::vector<Bag> &bags, const std::string &name)
{
  if (bags.empty())
    return false;
  for (const Bag &inner_bag : bags)
  {
    if (inner_bag.name == name)
    {
      return true;
    }
  }
  return false;
}

bool search_all_inner_bags(const std::vector<Bag> &bags, const std::vector<std::string> &names)
{
  if (bags.empty())
    return false;
  for (const Bag &inner_bag : bags)
  {
    for (const auto &name : names)
    {
      if (inner_bag.name == name)
      {
        return true;
      }
    }
  }
  return false;
}

auto Solution::solve_a() const -> int
{
  std::vector<std::string> has_shiny{"shiny gold"};
  int count{0};
  for (const auto &item : rules)
  {
    if (item.second.empty())
      continue;
    if (search_inner_bags(item.second, "shiny gold"))
    {
      has_shiny.push_back(item.first);
    }
  }

  for (const auto &item : rules)
  {
    if (item.second.empty())
      continue;
    if (search_all_inner_bags(item.second, has_shiny))
      ++count;
  }

  return count;
}

auto Solution::solve_b() -> int
{
  return 0;
}

auto main() -> int
{
  Solution day7{"../day7/input"};
  std::cout << "Part A" << std::endl;
  std::cout << day7.solve_a() << std::endl;
  return 0;
}