# 红黑树实现

这是一个完整的红黑树（Red-Black Tree）C++实现，包含了插入、删除操作以及完整的测试用例。该实现遵循标准的红黑树性质，并提供了树结构的可视化输出。

## 项目结构

```
rbtree/
├── src/
│   ├── BinarySearchTree.h  # 二叉搜索树基类
│   ├── RBTree.h           # 红黑树头文件
│   ├── RBTree.cpp         # 红黑树实现
│   └── CMakeLists.txt     # src目录的CMake配置
├── test/
│   ├── test_rbtree.cpp    # 测试用例
│   └── CMakeLists.txt     # test目录的CMake配置
├── build/                 # 构建输出目录
├── .vscode/              # VSCode配置
├── CMakeLists.txt        # 项目主CMake配置
├── build_and_run.sh      # 构建和运行脚本
└── README.md             # 本文档
```

## 功能特性

1. 标准红黑树操作：
   - 插入操作
   - 删除操作
   - 旋转操作（左旋/右旋）
   - 颜色调整

2. 红黑树性质验证：
   - 根节点为黑色
   - 红色节点的子节点必须为黑色
   - 从根到叶子的所有路径具有相同数量的黑色节点

3. 树结构可视化：
   - 使用ASCII字符展示树结构
   - 显示节点值和颜色信息
   - 显示节点间的连接关系

## 构建要求

- C++11或更高版本
- CMake 3.10或更高版本
- 支持的编译器：
  - Clang
  - GCC
  - MSVC

## 构建和运行

1. 使用提供的脚本：
```bash
chmod +x build_and_run.sh  # 添加执行权限
./build_and_run.sh        # 构建并运行测试
```

2. 手动构建：
```bash
mkdir -p build
cd build
cmake ..
make
./test/test_rbtree
```

## 测试用例

项目包含以下测试场景：

1. 基本操作测试：
   - 空树测试
   - 单节点插入
   - 左倾树插入
   - 右倾树插入

2. 复杂操作测试：
   - 多节点复杂插入
   - 删除叶子节点
   - 删除带一个子节点的节点
   - 删除带两个子节点的节点
   - 复杂删除场景
   - 删除不存在的节点

每个测试用例都会：
1. 执行相应的操作
2. 验证红黑树的所有性质
3. 可视化显示树的结构

## 预期输出

测试程序会输出类似以下格式的结果：

```
=== 测试插入单个节点 ===

树的结构：
[10B]

=== 测试左倾插入 ===
插入 30:
    [30B]    

插入 20:
    [30B]    
     └──    
[20R]        
```

其中：
- `[数字B]` 表示黑色节点
- `[数字R]` 表示红色节点
- `├─┴` 表示节点间的连接关系

## 使用示例

```cpp
#include "RBTree.h"

int main() {
    RBTree tree;
    
    // 插入节点
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    
    // 删除节点
    tree.remove(20);
    
    // 验证红黑树性质
    if (tree.isValidRBTree()) {
        std::cout << "红黑树性质验证通过" << std::endl;
    }
    
    return 0;
}
```

## 注意事项

1. 所有的修改操作（插入/删除）都会自动维护红黑树的性质
2. 可以使用 `isValidRBTree()` 方法在任何时候验证树的性质
3. 删除不存在的节点不会影响树的结构
4. 树的可视化输出会根据树的大小自动调整显示格式

## 调试

项目包含了VSCode的调试配置，可以使用VSCode的调试功能进行单步调试。在 `.vscode/launch.json` 中已配置好了调试设置。
