#include "Solution.h"
#include <iostream>
#include <set>

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

bool compareResults(const vector<vector<int>>& result, const vector<vector<int>>& expected) {
    if (result.size() != expected.size()) return false;
    
    set<vector<int>> resultSet(result.begin(), result.end());
    set<vector<int>> expectedSet(expected.begin(), expected.end());
    
    return resultSet == expectedSet;
}

void runTest(vector<int>& nums, const vector<vector<int>>& expected) {
    Solution solution;
    vector<vector<int>> result = solution.threeSum(nums);
    
    cout << "Input: nums = [";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    cout << "Output: ";
    printResult(result);
    
    cout << "Expected: ";
    printResult(expected);
    
    bool passed = compareResults(result, expected);
    cout << "Test " << (passed ? "PASSED" : "FAILED") << endl << endl;
}

int main() {
    // Test case 1
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> expected1 = {{-1,-1,2},{-1,0,1}};
    runTest(nums1, expected1);
    
    // Test case 2
    vector<int> nums2 = {0,1,1};
    vector<vector<int>> expected2 = {};
    runTest(nums2, expected2);
    
    // Test case 3
    vector<int> nums3 = {0,0,0};
    vector<vector<int>> expected3 = {{0,0,0}};
    runTest(nums3, expected3);
    
    return 0;
}
