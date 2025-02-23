#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct BaseNode {
    int data;
    BaseNode* left;
    BaseNode* right;
    BaseNode* parent;
    
    BaseNode(int value) : data(value), left(nullptr), 
                         right(nullptr), parent(nullptr) {}
    virtual ~BaseNode() = default;
};

class BinarySearchTree {
protected:
    BaseNode* root;

    // 内部工具函数
    virtual BaseNode* createNode(int value) {
        return new BaseNode(value);
    }

    void transplantBase(BaseNode* u, BaseNode* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    BaseNode* minimumBase(BaseNode* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    BaseNode* maximumBase(BaseNode* x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }

    void clearRecursiveBase(BaseNode* node) {
        if (node != nullptr) {
            clearRecursiveBase(node->left);
            clearRecursiveBase(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}
    virtual ~BinarySearchTree() {
        clearRecursiveBase(root);
    }

    // 基本搜索树操作
    virtual void insert(BaseNode* z) {
        BaseNode* y = nullptr;
        BaseNode* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    virtual void remove(int value) {
        BaseNode* z = search(root, value);
        if (z == nullptr) return;

        if (z->left == nullptr) {
            transplantBase(z, z->right);
        } else if (z->right == nullptr) {
            transplantBase(z, z->left);
        } else {
            BaseNode* y = minimumBase(z->right);
            if (y->parent != z) {
                transplantBase(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplantBase(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    bool search(int value) const {
        return search(root, value) != nullptr;
    }

    void clear() {
        clearRecursiveBase(root);
        root = nullptr;
    }

protected:
    BaseNode* search(BaseNode* x, int value) const {
        while (x != nullptr && value != x->data) {
            if (value < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }

    BaseNode* getRoot() const { return root; }
};

#endif // BINARY_SEARCH_TREE_H 