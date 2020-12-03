#include <fstream>
#include <iostream>
#include <string>
#include <queue>

class Solution {
public:
    Solution(std::string filePath)
    {
        std::ifstream input{filePath, std::ios::binary};
        if (input.fail()) {
            std::cout << "Error opening " << filePath;
        }
        std::string line;
        while (std::getline(input, line))
        {
            m_inputQueue.push(line);
        }
    }

    int helper(int right, int down);
    int solveA();
    uint64_t solveB();
    std::queue<std::string> m_inputQueue;
};

int Solution::helper(int right, int down)
{
    std::queue<std::string> queen{m_inputQueue};
    int currentIndex = 0;
    int treeCount = 0;
    while (queen.size())
    {
        std::string row = queen.front();
        if(currentIndex !=0 ) {
            while (row.size() <= currentIndex) {
                row += row;
            }
            if (row[currentIndex] == '#') ++treeCount;
        }
        currentIndex+=right;
        for (int i = 0; i < down; ++i) {
            if(queen.size())
                 queen.pop();
        }
    }

    return treeCount;
}

int Solution::solveA()
{
    return helper(3,1);
}

uint64_t Solution::solveB()
{ 
    return helper(1,1) *
           helper(3,1) *
           helper(5,1) *
           helper(7,1) *
           helper(1,2);
}

int main()
{
    Solution day3{"../day3/input"};
    std::cout << "Part A" << std::endl;
    std::cout << day3.solveA() << std::endl;
    std::cout << "Part B" << std::endl;
    std::cout << day3.solveB() << std::endl;
    return 0;
}