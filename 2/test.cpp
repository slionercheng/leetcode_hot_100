#include <iostream>
#include <cassert>
#include "solution.cpp"

// 用于打印结果的辅助函数
void printResult(const vector<vector<string>>& result) {
    cout << "[";
    for (const auto& group : result) {
        cout << "[";
        for (size_t i = 0; i < group.size(); ++i) {
            cout << "\"" << group[i] << "\"";
            if (i < group.size() - 1) cout << ",";
        }
        cout << "]";
    }
    cout << "]" << endl;
}

// 用于比较两个结果是否相等的辅助函数
bool compareResults(vector<vector<string>>& result1, vector<vector<string>>& result2) {
    if (result1.size() != result2.size()) return false;
    
    // 对每个组内的字符串排序
    for (auto& group : result1) {
        sort(group.begin(), group.end());
    }
    for (auto& group : result2) {
        sort(group.begin(), group.end());
    }
    
    // 对组进行排序
    sort(result1.begin(), result1.end());
    sort(result2.begin(), result2.end());
    
    return result1 == result2;
}

void runTests() {
    Solution solution;
    
    // Test case 1
    vector<string> test1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> expected1 = {{"bat"}, {"nat","tan"}, {"ate","eat","tea"}};
    auto result1 = solution.groupAnagrams(test1);
    assert(compareResults(result1, expected1));
    cout << "Test case 1 passed!" << endl;
    cout << "Input: ";
    for (const auto& s : test1) cout << s << " ";
    cout << "\nOutput: ";
    printResult(result1);
    
    // Test case 2
    vector<string> test2 = {""};
    vector<vector<string>> expected2 = {{""}};
    auto result2 = solution.groupAnagrams(test2);
    assert(compareResults(result2, expected2));
    cout << "Test case 2 passed!" << endl;
    
    // Test case 3
    vector<string> test3 = {"a"};
    vector<vector<string>> expected3 = {{"a"}};
    auto result3 = solution.groupAnagrams(test3);
    assert(compareResults(result3, expected3));
    cout << "Test case 3 passed!" << endl;
}

int main() {
    runTests();
    return 0;
} 