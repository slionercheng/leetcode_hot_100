#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Problem: Two Sum
    // Find two numbers in the array that add up to target
    // Return their indices
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if(num_map.find(complement) != num_map.end()) {
                vector<int> result;
                result.push_back(num_map[complement]);
                result.push_back(i);
                return result;
            }
            num_map[nums[i]] = i;
        }
        return vector<int>();
    }
};

#endif 