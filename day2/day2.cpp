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
    std::string partB();
private:
    std::ifstream              m_input;
    std::vector<std::string>   m_inputVector;

    int countCharacter(char character, std::string id);

    std::string findIntersection(std::string first, std::string second);
};

int Solution::countCharacter(char character, std::string id)
{
    return std::count(id.begin(), id.end(), character);
}


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


std::string Solution::findIntersection(std::string first, std::string second)
{
    auto first1 = first.begin();
    auto last1 = first.end();
    auto first2 = second.begin();
    auto last2 = second.end();
    std::string output{""};

    while (first1 != last1 && first2 != last2) {
        if (*first1 == *first2) {
            output += *first1;
        }
        ++first1; ++first2;
    }
    return output;
}

std::string Solution::partB()
{
    std::string result{""};

    for(auto id = m_inputVector.begin(); id != m_inputVector.end(); ++id) {
        for(auto idCompare = id+1; idCompare != m_inputVector.end(); ++idCompare) {
            std::string matchedID = findIntersection(*id, *idCompare);
            if (matchedID.size() == id->size()-1 &&
                matchedID.size() == idCompare->size()-1 &&
                result.size() < matchedID.size()) {
                result = matchedID;
            }
        }
    }

    return result;
}

int main()
{
    Solution solve{"../day2/input"};
    std::cout << "Part A" << std::endl;
    std::cout << solve.partA() << std::endl;

    std::cout << "Part B" << std::endl;
    std::cout << solve.partB() << std::endl;
    return 0;
}