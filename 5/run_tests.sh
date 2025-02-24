#!/bin/bash

# Compile the code
g++ -std=c++14 container_with_most_water.cpp test_container_with_most_water.cpp -o container_tests

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."
    echo "----------------------------------------"
    # Run the tests
    ./container_tests
else
    echo "Compilation failed!"
fi
