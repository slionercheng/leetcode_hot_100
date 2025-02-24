#include <algorithm>
#include "container_with_most_water.h"

int Solution::maxArea(std::vector<int>& height) {
    // TODO: Implement this function
    // The function should return the maximum area of water that can be contained
    // between any two vertical lines in the height array

    int left = 0;
    int right = height.size() - 1;
    int maxArea = 0;

    while (left < right) {
        int area = std::min(height[left], height[right]) * (right - left);

        maxArea = std::max(maxArea, area);

        if (height[left] > height[right]) {
            right--;
        } else {
            left++;
        }
    }

    return maxArea;
}
