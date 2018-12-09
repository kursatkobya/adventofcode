#include <climits>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

class Solution {
public:
    Solution(std::string filePath) :
        m_input {filePath, std::ios::binary},
        m_solutionA {0},
        m_solutionB {INT_MIN}
    {
        if (m_input.fail()) {
            std::cout << "Error opening " << filePath;
        }
    }

    int solveA();
    int solveB();
private:
    std::ifstream      m_input;
    std::vector<int>   m_inputVector;
    int                m_solutionA;
    int                m_solutionB;
    std::unordered_map<int, int> m_frequency;
};

int Solution::solveA()
{
    std::string str;
    while (std::getline(m_input, str))
    {
        auto diff = std::stoi(str);
        m_inputVector.push_back(diff);
        m_solutionA += diff;
        if (m_frequency.count(m_solutionA) > 0) {
            m_solutionB = m_solutionA;
        }
        m_frequency[m_solutionA]++;
    }

    return m_solutionA;
}

int Solution::solveB()
{
    int diff{m_solutionA};
    while (m_solutionB == INT_MIN)
    {
        for (auto anomaly : m_inputVector) {
            diff += anomaly;
            if (m_frequency.count(diff) > 0) {
                 m_solutionB = diff;
                break;
            }
            m_frequency[diff]++;
        }
    }

    return m_solutionB;
}

int main()
{
    std::cout << "Side A" << std::endl;
    Solution side_A{"../day1/input"};
    std::cout << side_A.solveA() << std::endl;

    std::cout << "Side B" << std::endl;
    std::cout << side_A.solveB() << std::endl;
    return 0;
}