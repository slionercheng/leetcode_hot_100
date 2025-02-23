#include "RBTree.h"
#include <vector>

void RBTree::insert(int value) {
    // 先调用创建节点

    BaseNode* z = createNode(value);

    // 调用基类的插入
    BinarySearchTree::insert(z);
    
    // 修复红黑树性质
    insertFixup(z);
}

void RBTree::remove(int value) {
    // 查找要删除的节点
    BaseNode* z = search(root, value);
    if (z == nullptr) {
        return;
    }

    // 修复红黑树性质
    deleteFixup(z);
}

void RBTree::leftRotate(BaseNode* x) {
    // 实现左旋操作
    BaseNode* y = x->right;

    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(BaseNode* x) {
    // 实现右旋操作
    BaseNode *y = x->left;

    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void RBTree::insertFixup(BaseNode* z) {
    // 实现插入后的修复操作
    while (getColor(z->parent) == RED) {
        if (z->parent == z->parent->parent->left) {  // 父节点是祖父节点的左子节点
            BaseNode* y = z->parent->parent->right;   // 叔叔节点
            
            if (getColor(y) == RED) {  // Case 1: 叔叔是红色
                setColor(z->parent, BLACK);
                setColor(y, BLACK);
                setColor(z->parent->parent, RED);
                z = z->parent->parent;
            } else {  // 叔叔是黑色
                if (z == z->parent->right) {  // Case 2: z是右子节点
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3
                setColor(z->parent, BLACK);
                setColor(z->parent->parent, RED);
                rightRotate(z->parent->parent);
            }
        } else {  // 父节点是祖父节点的右子节点（镜像情况）
            BaseNode* y = z->parent->parent->left;
            
            if (getColor(y) == RED) {
                setColor(z->parent, BLACK);
                setColor(y, BLACK);
                setColor(z->parent->parent, RED);
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                setColor(z->parent, BLACK);
                setColor(z->parent->parent, RED);
                leftRotate(z->parent->parent);
            }
        }
    }
    setColor(getRoot(), BLACK);  // 确保根节点为黑色

    return;
}

void RBTree::changeNodeData(BaseNode* x, BaseNode* y) {
    int data = x->data;
    x->data = y->data;
    y->data = data;
    return;
}

void RBTree::DeleteEdgeNode(BaseNode* x) {
    // 1.如果删除的节点为根节点，则直接删除即可
    if(x->parent == nullptr) {
        root = nullptr;
        delete x;
        return;
    }

    if(x->parent->left == x) {
        x->parent->left = nullptr;
    } else {
        x->parent->right = nullptr;
    }
    
    delete x;
}

bool RBTree::isValidRBTree() const {
    // 检查所有红黑树性质
    return isRootBlack() && 
           !hasRedParentRedChild() && 
           hasValidBlackHeight();
}

bool RBTree::isRootBlack() const {
    if (root == nullptr) return true;
    Node* rootNode = static_cast<Node*>(root);
    return rootNode->color == BLACK;
}

bool RBTree::hasRedParentRedChild() const {
    if (root == nullptr) return false;
    
    // 使用层序遍历检查所有节点
    std::vector<BaseNode*> queue;
    queue.push_back(root);
    
    while (!queue.empty()) {
        BaseNode* current = queue.front();
        queue.erase(queue.begin());
        
        Node* currentNode = static_cast<Node*>(current);
        
        // 如果当前节点是红色，检查其子节点
        if (currentNode->color == RED) {
            if (current->left != nullptr) {
                Node* leftChild = static_cast<Node*>(current->left);
                if (leftChild->color == RED) return true;
            }
            if (current->right != nullptr) {
                Node* rightChild = static_cast<Node*>(current->right);
                if (rightChild->color == RED) return true;
            }
        }
        
        // 将子节点加入队列
        if (current->left != nullptr) queue.push_back(current->left);
        if (current->right != nullptr) queue.push_back(current->right);
    }
    
    return false;
}

int RBTree::getBlackHeight(BaseNode* node) const {
    if (node == nullptr) return 0;
    
    Node* currentNode = static_cast<Node*>(node);
    int blackHeight = currentNode->color == BLACK ? 1 : 0;
    
    // 递归计算左右子树的黑色节点高度
    int leftHeight = getBlackHeight(node->left);
    int rightHeight = getBlackHeight(node->right);
    
    // 如果左右子树的黑节点高度不相等，或者任一子树无效，返回-1
    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
        return -1;
    }
    
    return blackHeight + leftHeight;
}

bool RBTree::hasValidBlackHeight() const {
    return getBlackHeight(root) != -1;
}

void RBTree::deleteFixup(BaseNode* x) {
    // 1. 如果有左孩子/右孩子，则往下交换值
    while(x->left != nullptr || x->right != nullptr) {
        if(x->left != nullptr) {
            changeNodeData(x, x->left);
            x = x->left;
        } else if(x->right != nullptr) {
            changeNodeData(x, x->right);
            x = x->right;
        }
    }

    // 2. 当没有左右孩子，则删除该节点，此时分情况讨论可能的颜色
    // 2.1 如果是红色，则直接删除即可
    Node *cur = static_cast<Node*>(x);

    if(cur->color == BLACK) {
        if (cur == cur->parent->left) {
            Node* brother = static_cast<Node*>(cur->parent->right);

            if(getColor(cur->parent) == BLACK) {
                if (getColor(brother) == BLACK) {
                    // 兄弟节点是黑色
                    if (brother->left == nullptr && brother->right == nullptr) {
                        // 兄弟节点没有子节点，直接变色
                        setColor(brother, RED);
                    } else if (brother->left != nullptr) {
                        // 兄弟节点有左子节点
                        Node* brother_left = static_cast<Node*>(brother->left);
                        rightRotate(brother);
                        leftRotate(brother_left);
                        setColor(brother_left, BLACK);
                    } else if (brother->right != nullptr) {
                        // 兄弟节点有右子节点
                        leftRotate(brother);
                        setColor(brother, getColor(cur->parent));
                        setColor(cur->parent, BLACK);
                        setColor(brother->right, BLACK);
                    }
                } else {
                    // 兄弟节点是红色
                    leftRotate(brother);
                    setColor(brother, BLACK);
                    setColor(cur->parent, RED);
                    deleteFixup(cur); // 递归处理
                }
            } else {
                // 父节点是红色
                if (brother->left == nullptr && brother->right == nullptr) {
                    setColor(brother, RED);
                    setColor(cur->parent, BLACK);
                } else if (brother->right != nullptr) {
                    leftRotate(brother);
                    setColor(brother, getColor(cur->parent));
                    setColor(cur->parent, BLACK);
                    setColor(brother->right, BLACK);
                } else {
                    Node* brother_left = static_cast<Node*>(brother->left);
                    rightRotate(brother);
                    leftRotate(brother_left);
                    setColor(brother_left, BLACK);
                }
            }
        } else {
            // 对称情况：当前节点是右子节点
            Node* brother = static_cast<Node*>(cur->parent->left);

            if(getColor(cur->parent) == BLACK) {
                if (getColor(brother) == BLACK) {
                    // 兄弟节点是黑色
                    if (brother->left == nullptr && brother->right == nullptr) {
                        // 兄弟节点没有子节点，直接变色
                        setColor(brother, RED);
                    } else if (brother->right != nullptr) {
                        // 兄弟节点有右子节点
                        Node* brother_right = static_cast<Node*>(brother->right);
                        leftRotate(brother);
                        rightRotate(brother_right);
                        setColor(brother_right, BLACK);
                    } else if (brother->left != nullptr) {
                        // 兄弟节点有左子节点
                        rightRotate(brother);
                        setColor(brother, getColor(cur->parent));
                        setColor(cur->parent, BLACK);
                        setColor(brother->left, BLACK);
                    }
                } else {
                    // 兄弟节点是红色
                    rightRotate(brother);
                    setColor(brother, BLACK);
                    setColor(cur->parent, RED);
                    deleteFixup(cur); // 递归处理
                }
            } else {
                // 父节点是红色
                if (brother->left == nullptr && brother->right == nullptr) {
                    setColor(brother, RED);
                    setColor(cur->parent, BLACK);
                } else if (brother->left != nullptr) {
                    rightRotate(brother);
                    setColor(brother, getColor(cur->parent));
                    setColor(cur->parent, BLACK);
                    setColor(brother->left, BLACK);
                } else {
                    Node* brother_right = static_cast<Node*>(brother->right);
                    leftRotate(brother);
                    rightRotate(brother_right);
                    setColor(brother_right, BLACK);
                }
            }
        }
    }

    DeleteEdgeNode(cur);
}
