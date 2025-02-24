#include <iostream>
#include <vector>
#include <string>
#include "container_with_most_water.h"

// Simple test framework
class TestCase {
private:
    int passed = 0;
    int total = 0;

    void printResult(const std::string& testName, bool success) {
        total++;
        if (success) {
            passed++;
            std::cout << "✓ " << testName << " passed" << std::endl;
        } else {
            std::cout << "✗ " << testName << " failed" << std::endl;
        }
    }

public:
    template<typename T>
    void assertEqual(const std::string& testName, const T& expected, const T& actual) {
        bool success = expected == actual;
        printResult(testName, success);
        if (!success) {
            std::cout << "  Expected: " << expected << std::endl;
            std::cout << "  Got: " << actual << std::endl;
        }
    }

    void summary() {
        std::cout << "\nTest Summary:\n";
        std::cout << "Passed: " << passed << "/" << total << " tests" << std::endl;
        if (passed == total) {
            std::cout << "All tests passed!" << std::endl;
        } else {
            std::cout << (total - passed) << " tests failed." << std::endl;
        }
    }
};

int main() {
    TestCase tester;
    Solution solution;

    // Test case 1: Example from problem description
    {
        std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        tester.assertEqual("Example test case", 49, solution.maxArea(height));
    }

    // Test case 2: Minimal case
    {
        std::vector<int> height = {1, 1};
        tester.assertEqual("Minimal test case", 1, solution.maxArea(height));
    }

    // Test case 3: All same height
    {
        std::vector<int> height = {4, 4, 4, 4};
        tester.assertEqual("All same height", 12, solution.maxArea(height));
    }

    // Test case 4: Increasing height
    {
        std::vector<int> height = {1, 2, 3, 4, 5};
        tester.assertEqual("Increasing height", 6, solution.maxArea(height));
    }

    // Test case 5: Decreasing height
    {
        std::vector<int> height = {5, 4, 3, 2, 1};
        tester.assertEqual("Decreasing height", 6, solution.maxArea(height));
    }

    tester.summary();
    return 0;
}
