#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int nonZeroPos = 0;  // 指向待填入非零元素的位置
        
        // 第一次遍历：将所有非零元素移到数组前面
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (i != nonZeroPos) {
                    swap(nums[nonZeroPos], nums[i]);
                }
                nonZeroPos++;
            }
        }
    }
};

// Test function to print vector
void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // Test case 1
    vector<int> nums1;
    nums1.push_back(0);
    nums1.push_back(1);
    nums1.push_back(0);
    nums1.push_back(3);
    nums1.push_back(12);
    cout << "Test case 1:" << endl;
    cout << "Input: ";
    printVector(nums1);
    solution.moveZeroes(nums1);
    cout << "Output: ";
    printVector(nums1);
    cout << endl;
    
    // Test case 2
    vector<int> nums2;
    nums2.push_back(0);
    cout << "Test case 2:" << endl;
    cout << "Input: ";
    printVector(nums2);
    solution.moveZeroes(nums2);
    cout << "Output: ";
    printVector(nums2);
    
    return 0;
}
