#include <iostream>
#include "solution.h"

void test_case_1() {
    Solution s;
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result = s.trap(height);
    std::cout << "Test Case 1:" << std::endl;
    std::cout << "Expected: 6" << std::endl;
    std::cout << "Got: " << result << std::endl;
    std::cout << (result == 6 ? "PASSED" : "FAILED") << std::endl;
}

void test_case_2() {
    Solution s;
    std::vector<int> height = {4,2,0,3,2,5};
    int result = s.trap(height);
    std::cout << "Test Case 2:" << std::endl;
    std::cout << "Expected: 9" << std::endl;
    std::cout << "Got: " << result << std::endl;
    std::cout << (result == 9 ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    test_case_1();
    std::cout << "------------------------" << std::endl;
    test_case_2();
    return 0;
}
