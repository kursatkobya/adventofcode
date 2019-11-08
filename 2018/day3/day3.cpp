#include <array>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Solution {
public:
    Solution(std::string filePath):
        m_area{}
    {
        std::ifstream  inputFile {filePath, std::ios::binary};
        if (inputFile.fail()) {
            std::cout << "Error opening " << filePath;
        }

        std::string str;
        while (std::getline(inputFile, str))
        {
            m_inputVector.push_back(str);
        }

        parseClaims();
    }

    struct Claim  {
        int    m_id;
        int    m_left;
        int    m_top;
        int    m_wide;
        int    m_tall;
    };

    int partA();
    std::string partB();
private:
    std::vector<std::string>      m_inputVector;
    std::vector<Claim>            m_claimList;
    std::array<std::array<int, 1000>, 1000> m_area;

    void parseClaims();
};

void Solution::parseClaims()
{
    for (auto unparsedClaim:m_inputVector) {
        Claim claim;
        std::stringstream parserPlate{unparsedClaim};
        std::string parserFork{""};
        parserPlate >> parserFork;
        claim.m_id = std::stoi(parserFork.substr(1));
        parserPlate >> parserFork;  //@
        parserPlate >> parserFork;

        std::string delimiter = ",";
        size_t pos = parserFork.find(delimiter);
        claim.m_left = std::stoi(parserFork.substr(0, pos));
        claim.m_top = std::stoi(parserFork.substr(pos+1, parserFork.size()-1));

        parserPlate >> parserFork;
        delimiter = "x";
        pos = parserFork.find(delimiter);
        claim.m_wide = std::stoi(parserFork.substr(0, pos));
        claim.m_tall = std::stoi(parserFork.substr(pos+1));
        m_claimList.push_back(claim);

        for (auto vertical = claim.m_top; vertical < claim.m_tall + claim.m_top;
                ++vertical) {
            for (auto horizontal = claim.m_left;
                    horizontal < claim.m_wide + claim.m_left; ++horizontal) {
                ++m_area[vertical][horizontal];
            }
        }
    }
}

int Solution::partA()
{
    int resultA{0};
    for (auto row:m_area) {
        for (auto column:row) {
            if (column > 1) {
                ++resultA;
            }
        }
    }

    return resultA;
}

std::string Solution::partB()
{
    return "";
}

int main()
{
    Solution solve{"../day3/input"};
    std::cout << "Part A" << std::endl;
    std::cout << solve.partA() << std::endl;

    std::cout << "Part B" << std::endl;
    std::cout << solve.partB() << std::endl;
    return 0;
}