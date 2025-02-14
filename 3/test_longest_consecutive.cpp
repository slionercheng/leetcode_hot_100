#include <iostream>
#include <vector>
#include <cassert>
#include "longest_consecutive_sequence.cpp"

void runTest() {
    Solution solution;
    
    // Test case 1
    vector<int> nums1 = {100,4,200,1,3,2};
    assert(solution.longestConsecutive(nums1) == 4);
    cout << "Test case 1 passed!" << endl;
    
    // Test case 2
    vector<int> nums2 = {0,3,7,2,5,8,4,6,0,1};
    assert(solution.longestConsecutive(nums2) == 9);
    cout << "Test case 2 passed!" << endl;
    
    // Additional test cases
    // Empty array
    vector<int> nums3 = {};
    assert(solution.longestConsecutive(nums3) == 0);
    cout << "Test case 3 (empty array) passed!" << endl;
    
    // Single element
    vector<int> nums4 = {1};
    assert(solution.longestConsecutive(nums4) == 1);
    cout << "Test case 4 (single element) passed!" << endl;
    
    // Duplicate elements
    vector<int> nums5 = {1,1,2,2,3,3};
    assert(solution.longestConsecutive(nums5) == 3);
    cout << "Test case 5 (duplicate elements) passed!" << endl;
    
    cout << "All test cases passed!" << endl;
}

int main() {
    runTest();
    return 0;
} 