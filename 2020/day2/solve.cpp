#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
        Solution(std::string filePath) : m_input{filePath, std::ios::binary}
        {
                if (m_input.fail())
                {
                        std::cout << "Error opening " << filePath;
                }
                std::string line;
                while (std::getline(m_input, line))
                {
                        pwd item;
                        std::uint32_t start_pos = 0;
                        std::uint32_t end_pos = line.find("-");
                        std::string min = line.substr(start_pos, end_pos);
                        item.min = std::stoi(min);
                        start_pos = end_pos + 1;
                        end_pos = line.find(" ", start_pos);
                        std::string max = line.substr(start_pos, end_pos - start_pos);
                        item.max = std::stoi(max);
                        start_pos = end_pos + 1;
                        end_pos = line.find(" ", start_pos);
                        std::string character = line.substr(start_pos, end_pos - start_pos);
                        item.key = character[0];
                        start_pos = end_pos + 1;
                        end_pos = line.size();
                        item.password = line.substr(start_pos, end_pos - start_pos);
                        m_inputVector.push_back(item);
                }
        }

        int solveA();
        int solveB();
        class pwd
        {
        public:
                int min = 0;
                int max = 0;
                char key;
                std::string password;
        };

        std::vector<pwd> m_inputVector;

private:
        std::ifstream m_input;
};

int Solution::solveA()
{
        int validPwd = 0;
        std::vector<pwd> testVec = m_inputVector;
        while (testVec.size())
        {
                pwd item = testVec.back();
                int count = 0;
                for (int i = 0; i < item.password.size(); ++i)
                {
                        if (item.password[i] == item.key)
                                ++count;
                }
                if (item.min <= count && count <= item.max)
                        ++validPwd;
                testVec.pop_back();
        }

        return validPwd;
}

int Solution::solveB()
{
        int validPwd = 0;
        while (m_inputVector.size())
        {
                pwd item = m_inputVector.back();
                bool min_exist = false, max_exist = false;
                if (item.password[item.min - 1] == item.key)
                        min_exist = true;
                if (item.password[item.max - 1] == item.key)
                        max_exist = true;
                if (min_exist xor max_exist)
                        ++validPwd;
                m_inputVector.pop_back();
        }

        return validPwd;
}

int main()
{
        Solution day2{"../day2/input"};
        std::cout << "Part A" << std::endl;
        std::cout << day2.solveA() << std::endl;
        std::cout << "Part B" << std::endl;
        std::cout << day2.solveB() << std::endl;
        return 0;
}