#ifndef CONTAINER_WITH_MOST_WATER_H
#define CONTAINER_WITH_MOST_WATER_H

#include <vector>

class Solution {
public:
    /**
     * @brief Find the maximum area of water that can be contained between two vertical lines
     * 
     * @param height Vector of heights where index represents x-coordinate and value represents height
     * @return int Maximum area of water that can be contained
     */
    int maxArea(std::vector<int>& height);
};

#endif // CONTAINER_WITH_MOST_WATER_H
