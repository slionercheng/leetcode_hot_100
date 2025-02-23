#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include "../src/RBTree.h"

// 用于存储节点显示信息的结构
struct DisplayNode {
    std::string data;  // 节点显示的内容
    int position;      // 节点在其层的位置
    int level;         // 节点的层级
};

// 获取节点的显示字符串
std::string getNodeStr(Node* node) {
    if (!node) return "  ";
    return "[" + std::to_string(node->data) + 
           (node->color == RED ? "R" : "B") + "]";
}

// 计算树的高度
int getTreeHeight(Node* root) {
    if (!root) return 0;
    return 1 + std::max(getTreeHeight(static_cast<Node*>(root->left)), 
                       getTreeHeight(static_cast<Node*>(root->right)));
}

// 用于打印树的辅助函数
void printTree(const RBTree& tree) {
    Node* root = tree.getRoot();
    if (!root) {
        std::cout << "空树" << std::endl;
        return;
    }

    int height = getTreeHeight(root);
    int maxWidth = (1 << height) - 1;
    std::vector<std::vector<std::string> > display(height, std::vector<std::string>(maxWidth, "  "));
    
    // 首先收集所有节点的信息
    std::vector<std::pair<Node*, int> > stack;  // 存储节点和位置
    stack.push_back({root, maxWidth/2});

    int level = 0;
    int nodesInCurrentLevel = 1;
    int nodesProcessed = 0;

    while (!stack.empty()) {
        int currentLevelSize = stack.size();
        int spacing = 1 << (height - level - 1);

        for (int i = 0; i < currentLevelSize; i++) {
            auto [node, pos] = stack[i];
            if (node) {
                display[level][pos] = getNodeStr(node);
                if (node->left) {
                    stack.push_back({static_cast<Node*>(node->left), pos - spacing/2});
                }
                if (node->right) {
                    stack.push_back({static_cast<Node*>(node->right), pos + spacing/2});
                }
            }
        }

        stack.erase(stack.begin(), stack.begin() + currentLevelSize);
        level++;
    }

    // 打印树结构
    std::cout << "\n树的结构：\n" << std::endl;
    
    // 打印每一层
    for (int level = 0; level < height; level++) {
        // 打印节点
        for (int pos = 0; pos < maxWidth; pos++) {
            std::cout << std::setw(4) << display[level][pos];
        }
        std::cout << std::endl;

        // 如果不是最后一层，打印连接线
        if (level < height - 1) {
            // 打印连接线
            for (int pos = 0; pos < maxWidth; pos++) {
                if (display[level][pos] != "  ") {
                    bool hasLeft = false;
                    bool hasRight = false;
                    
                    // 检查是否有左右子节点
                    for (int childPos = 0; childPos < maxWidth; childPos++) {
                        if (display[level + 1][childPos] != "  ") {
                            if (childPos < pos) hasLeft = true;
                            if (childPos > pos) hasRight = true;
                        }
                    }

                    // 打印连接线
                    if (hasLeft && hasRight) {
                        std::cout << " ├─┴";
                    } else if (hasLeft) {
                        std::cout << " └──";
                    } else if (hasRight) {
                        std::cout << " ├──";
                    } else {
                        std::cout << "    ";
                    }
                } else {
                    std::cout << "    ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

// 测试空树
void testEmptyTree() {
    std::cout << "\n=== 测试空树 ===" << std::endl;
    RBTree tree;
    assert(tree.getRoot() == nullptr);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试插入单个节点
void testSingleInsert() {
    std::cout << "\n=== 测试插入单个节点 ===" << std::endl;
    RBTree tree;
    tree.insert(10);
    assert(tree.getRoot()->data == 10);
    assert(tree.getNodeColor(10) == BLACK);  // 根节点必须是黑色
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试连续插入形成左倾树
void testLeftLeaningInsert() {
    std::cout << "\n=== 测试左倾插入 ===" << std::endl;
    RBTree tree;
    std::cout << "插入 30:" << std::endl;
    tree.insert(30);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "插入 20:" << std::endl;
    tree.insert(20);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "插入 10:" << std::endl;
    tree.insert(10);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试连续插入形成右倾树
void testRightLeaningInsert() {
    std::cout << "\n=== 测试右倾插入 ===" << std::endl;
    RBTree tree;
    std::cout << "插入 10:" << std::endl;
    tree.insert(10);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "插入 20:" << std::endl;
    tree.insert(20);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "插入 30:" << std::endl;
    tree.insert(30);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试复杂插入情况
void testComplexInsert() {
    std::cout << "\n=== 测试复杂插入 ===" << std::endl;
    RBTree tree;
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    
    for (int val : values) {
        std::cout << "\n插入 " << val << ":" << std::endl;
        tree.insert(val);
        assert(tree.isValidRBTree());
        printTree(tree);
    }
}

// 测试删除叶子节点
void testDeleteLeaf() {
    std::cout << "\n=== 测试删除叶子节点 ===" << std::endl;
    RBTree tree;
    // 构建一个简单的树
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    std::cout << "初始树:" << std::endl;
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除叶子节点 10:" << std::endl;
    tree.remove(10);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除叶子节点 30:" << std::endl;
    tree.remove(30);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试删除有一个子节点的节点
void testDeleteOneChild() {
    std::cout << "\n=== 测试删除带一个子节点的节点 ===" << std::endl;
    RBTree tree;
    // 构建测试树
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    std::cout << "初始树:" << std::endl;
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除节点 10:" << std::endl;
    tree.remove(10);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试删除有两个子节点的节点
void testDeleteTwoChildren() {
    std::cout << "\n=== 测试删除带两个子节点的节点 ===" << std::endl;
    RBTree tree;
    // 构建一个更复杂的树
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    for (int val : values) {
        tree.insert(val);
    }
    std::cout << "初始树:" << std::endl;
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除节点 20:" << std::endl;
    tree.remove(20);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试复杂删除情况
void testComplexDelete() {
    std::cout << "\n=== 测试复杂删除情况 ===" << std::endl;
    RBTree tree;
    // 构建一个复杂的树
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    for (int val : values) {
        tree.insert(val);
    }
    std::cout << "初始树:" << std::endl;
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除节点 18:" << std::endl;
    tree.remove(18);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除节点 7:" << std::endl;
    tree.remove(7);
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "删除节点 22:" << std::endl;
    tree.remove(22);
    assert(tree.isValidRBTree());
    printTree(tree);
}

// 测试删除不存在的节点
void testDeleteNonExistent() {
    std::cout << "\n=== 测试删除不存在的节点 ===" << std::endl;
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    std::cout << "初始树:" << std::endl;
    assert(tree.isValidRBTree());
    printTree(tree);
    
    std::cout << "尝试删除不存在的节点 30:" << std::endl;
    tree.remove(30);
    assert(tree.isValidRBTree());
    printTree(tree);
}

int main() {
    std::cout << "开始红黑树测试..." << std::endl;
    
    // 插入测试
    testEmptyTree();
    testSingleInsert();
    testLeftLeaningInsert();
    testRightLeaningInsert();
    testComplexInsert();
    
    // 删除测试
    testDeleteLeaf();
    testDeleteOneChild();
    testDeleteTwoChildren();
    testComplexDelete();
    testDeleteNonExistent();
    
    std::cout << "\n所有测试完成！" << std::endl;
    return 0;
} 