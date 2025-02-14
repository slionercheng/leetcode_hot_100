#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // Create a hash set for O(1) lookup

        std::unordered_set<int> NumSet(nums.begin(), nums.end());
        
        int maxLength = 0;
        for (int num : nums) {
            if (NumSet.find(num - 1) == NumSet.end()) {
                int currentNum = num;
                int currentLength = 1;
                while (NumSet.find(currentNum + 1) != NumSet.end()) {
                    currentNum++;
                    currentLength++;
                }
                maxLength = max(maxLength, currentLength);
            }
        }
        return maxLength;
    }
}; 