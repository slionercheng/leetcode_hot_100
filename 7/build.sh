#!/bin/bash

# 编译
g++ -std=c++11 solution.cpp test.cpp -o test

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功！"
    # 运行测试程序
    ./test
else
    echo "编译失败！"
    exit 1
fi
