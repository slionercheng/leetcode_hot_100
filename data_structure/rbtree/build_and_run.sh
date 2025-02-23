#!/bin/bash

# 创建并进入构建目录
mkdir -p build
cd build

# 运行 cmake 配置
echo "正在配置 CMake..."
cmake ..

# 编译项目
echo "正在编译项目..."
cmake --build .

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功！"
    
    # 运行测试程序
    echo "运行测试..."
    ./test/test_rbtree
else
    echo "编译失败！"
    exit 1
fi

# 返回到原目录
cd .. 