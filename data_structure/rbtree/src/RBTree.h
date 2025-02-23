#ifndef RBTREE_H
#define RBTREE_H

#include "BinarySearchTree.h"

enum Color {RED, BLACK};

struct Node : public BaseNode {
    Color color;
    
    Node(int value) : BaseNode(value), color(RED) {}
};

class RBTree : public BinarySearchTree {
protected:
    // 重写创建节点的方法
    BaseNode* createNode(int value) override {
        return new Node(value);
    }

    // 获取节点颜色的辅助函数
    Color getColor(BaseNode* n) {
        if (n == nullptr) return BLACK;
        return static_cast<Node*>(n)->color;
    }

    void setColor(BaseNode* n, Color c) {
        if (n != nullptr) {
            static_cast<Node*>(n)->color = c;
        }
    }

public:
    // 重写插入操作
    void insert(int value);
    
    // 重写删除操作
    void remove(int value) override;

    // 添加公开的访问方法
    Node* getRoot() const { 
        return static_cast<Node*>(BinarySearchTree::getRoot()); 
    }

    // 获取节点颜色的公开方法
    Color getNodeColor(int value) const {
        BaseNode* node = search(root, value);
        if (node == nullptr) return BLACK;
        return static_cast<Node*>(node)->color;
    }

private:
    // 红黑树特有的操作
    void leftRotate(BaseNode* x);
    void rightRotate(BaseNode* x);
    void insertFixup(BaseNode* z);
    void deleteFixup(BaseNode* x);
    void changeNodeData(BaseNode* x, BaseNode* y);
    void DeleteEdgeNode(BaseNode* x);

public:
    // 检查红黑树性质
    bool isValidRBTree() const;
    bool hasRedParentRedChild() const;
    bool hasValidBlackHeight() const;
    int getBlackHeight(BaseNode* node) const;
    bool isRootBlack() const;
};

#endif // RBTREE_H 