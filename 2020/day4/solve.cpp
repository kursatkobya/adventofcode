#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution
{
public:
        explicit Solution(const std::string &filePath)
        {
                std::ifstream input{filePath, std::ios::binary};
                if (input.fail())
                {
                        std::cout << "Error opening " << filePath;
                }
                std::string line;
                Passport currentPassport;
                std::string key;
                std::string value;
                while (std::getline(input, line, '\n'))
                {
                        if (line.empty())
                        {
                                m_passportList.push_back(currentPassport);
                                currentPassport.clear();
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
                                currentPassport[key] = value;
                        }
                }
        }

        using Passport = std::map<std::string, std::string>;

        static auto isPassPortValid(Passport pass) -> bool
        {
                std::vector<std::string> requiredFields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
                for (const auto &item : requiredFields)
                {
                        if (pass.find(item) == pass.end())
                        {
                                return false;
                        }
                }
                return true;
        }

        static auto isPassPortReallyValid(Passport pass) -> bool
        {
                try
                {
                        std::vector<std::string> requiredFields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
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
                                else
                                        return false;
                        }

                        std::vector<std::string> validColors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                        bool valid{false};
                        for (const auto &color : validColors)
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

        auto solveA() -> int;
        auto solveB() -> int;
        std::vector<Passport> m_passportList;
};

auto Solution::solveA() -> int
{
        int count{0};
        for (const auto &item : m_passportList)
        {
                if (isPassPortValid(item))
                        ++count;
        }
        return count;
}

auto Solution::solveB() -> int
{
        int count{0};
        for (const auto &item : m_passportList)
        {
                if (isPassPortReallyValid(item))
                        ++count;
        }
        return count;
}

auto main() -> int
{
        Solution day4{"../day4/input"};
        std::cout << "Part A" << std::endl;
        std::cout << day4.solveA() << std::endl;
        std::cout << "Part B" << std::endl;
        std::cout << day4.solveB() << std::endl;
        return 0;
}