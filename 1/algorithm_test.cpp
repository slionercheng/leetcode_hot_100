#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <chrono>
#include "solution.hpp"

using namespace std;

// Test case structure for Two Sum problem
struct TestCase {
    vector<int> nums;
    int target;
    vector<int> expected;
    string description;
};

// Run test function
void runTest(const TestCase& test, int caseNumber) {
    Solution solution;
    
    auto start = chrono::high_resolution_clock::now();
    vector<int> result = solution.twoSum(const_cast<vector<int>&>(test.nums), test.target);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> duration = end - start;
    
    cout << "Test Case #" << caseNumber << " (" << test.description << ")" << endl;
    cout << "Input array: ";
    for (int num : test.nums) {
        cout << num << " ";
    }
    cout << "\nTarget: " << test.target << endl;
    
    cout << "Expected output: [";
    for (size_t i = 0; i < test.expected.size(); i++) {
        cout << test.expected[i] << (i < test.expected.size() - 1 ? "," : "");
    }
    cout << "]" << endl;
    
    cout << "Actual output: [";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << (i < result.size() - 1 ? "," : "");
    }
    cout << "]" << endl;
    
    cout << "Execution time: " << duration.count() << " ms" << endl;
    
    bool passed = (result.size() == test.expected.size() &&
                  (result == test.expected || 
                   (result[0] == test.expected[1] && result[1] == test.expected[0])));
    
    if (passed) {
        cout << "Result: PASSED ✓" << endl;
    } else {
        cout << "Result: FAILED ✗" << endl;
    }
    cout << "------------------------" << endl;
}

int main() {
    vector<TestCase> testCases = {
        {{2, 7, 11, 15}, 9, {0, 1}, "Example 1: Standard case"},
        {{3, 2, 4}, 6, {1, 2}, "Example 2: Numbers in middle"},
        {{3, 3}, 6, {0, 1}, "Example 3: Same numbers"},
        {{1, 5, 8, 10, 13}, 18, {2, 3}, "Custom test: Larger array"}
    };
    cout << "Starting Two Sum Tests..." << endl;
    cout << "========================" << endl;
    
    int totalTests = testCases.size();
    int passedTests = 0;
    
    for (int i = 0; i < testCases.size(); i++) {
        runTest(testCases[i], i + 1);
        Solution solution;
        vector<int> result = solution.twoSum(testCases[i].nums, testCases[i].target);
        if (result == testCases[i].expected || 
            (result.size() == 2 && result[0] == testCases[i].expected[1] && 
             result[1] == testCases[i].expected[0])) {
            passedTests++;
        }
    }
    
    cout << "Testing Complete!" << endl;
    cout << "Passed: " << passedTests << "/" << totalTests << endl;
    
    return 0;
} 