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
                std::string str;
                while (std::getline(m_input, str))
                {
                        m_inputVector.push_back(std::stoi(str));
                }
        }

        int solveA();
        int solveB();

private:
        std::ifstream m_input;
        std::vector<int> m_inputVector;
};

int Solution::solveA()
{
        std::string str;
        for (int i = 0; i < m_inputVector.size() - 1; ++i)
        {
                for (int j = i + 1; j < m_inputVector.size(); ++j)
                {
                        if (m_inputVector[i] + m_inputVector[j] == 2020)
                        {
                                return m_inputVector[i] * m_inputVector[j];
                        }
                }
        }

        return 0;
}

int Solution::solveB()
{
        std::string str;
        for (int i = 0; i < m_inputVector.size() - 2; ++i)
        {
                for (int j = i + 1; j < m_inputVector.size() - 1; ++j)
                {
                        for (int k = j + 1; k < m_inputVector.size(); ++k)
                        {
                                if (m_inputVector[i] + m_inputVector[j] + m_inputVector[k] == 2020)
                                {
                                        return m_inputVector[i] * m_inputVector[j] * m_inputVector[k];
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
        std::cout << day1.solveA() << std::endl;
        std::cout << "Part B" << std::endl;
        std::cout << day1.solveB() << std::endl;

        return 0;
}