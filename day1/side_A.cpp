#include <iostream>
#include <fstream>
#include <string>

class Solution {
public:
    Solution(std::string filePath) :
        m_input {filePath, std::ios::binary},
        m_solution {0}
    {
        if (m_input.fail()) {
            std::cout << "Error opening " << filePath;
        }
    }

    int solve();
private:
    std::ifstream m_input;
    int           m_solution;
};

int Solution::solve()
{
    std::string str;
    while (std::getline(m_input, str))
    {
        auto diff = std::stoi(str.substr(1));
        if (str[0] == '-') {
            m_solution -= diff;
        } else {
            m_solution += diff;
        }
    }

    return m_solution;
}

int main()
{
    Solution side_A{"../input"};
    std::cout << side_A.solve() << std::endl;
    return 0;
}