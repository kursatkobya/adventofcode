#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    Solution(std::string filePath) :
        m_input {filePath, std::ios::binary}
    {
        if (m_input.fail()) {
            std::cout << "Error opening " << filePath;
        }

        std::string str;
        while (std::getline(m_input, str))
        {
            m_inputVector.push_back(str);
        }

    }

    int partA();
    int partB();
private:
    std::ifstream              m_input;
    std::vector<std::string>   m_inputVector;

    int countCharacter(char character, std::string id) {
        return std::count(id.begin(), id.end(), character);
    }
};

int Solution::partA()
{
    int twos{0}, threes{0};
    for (auto id : m_inputVector) {
        bool twoFound{false}, threeFound{false};
        for (auto character : id) {
            auto currCount = countCharacter(character, id);

            if (!twoFound && currCount == 2) {
                ++twos;
                twoFound = true;
            }

            if (!threeFound && currCount == 3) {
                ++threes;
                threeFound = true;
            }
        }
    }
    return twos * threes;
}

int Solution::partB()
{
    return 1;
}

int main()
{
    Solution solve{"../day2/input"};
    std::cout << "Part A" << std::endl;
    std::cout << solve.partA() << std::endl;

    return 0;
}