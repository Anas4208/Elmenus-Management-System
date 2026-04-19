#!/bin/bash

set -e  # Exit on error

echo "========================================="
echo "  Elmenus System - Coverage Analysis"
echo "========================================="

# Clean old files
echo "Cleaning old build files..."
rm -f *.o *.gcda *.gcno main compile_commands.json coverage.xml coverage.html

# Compile with coverage flags
echo "Compiling with coverage support..."
g++ -std=c++17 -fprofile-arcs -ftest-coverage -g -O0 \
    User.cpp Customer.cpp DeliveryDriver.cpp main.cpp -o main

# Run with test input
echo "Running tests..."
if [ -f test_input.txt ]; then
    ./main < test_input.txt
else
    echo "Warning: test_input.txt not found. Running manual input simulation..."
    echo -e "1\nC001\nJohn Doe\n1234567890\n123 Main St\n1\nC002\nJane Smith\n0987654321\n456 Oak Ave\n2\nD001\nBob Driver\n5551234567\nVan\n3\nC001\n4\nD001\n6" | ./main
fi

# Generate coverage report
echo "Generating coverage report..."
if command -v gcovr &> /dev/null; then
    gcovr --root . --xml -o coverage.xml
    gcovr --root . --html -o coverage.html
    gcovr --root . --txt
else
    echo "gcovr not found. Installing..."
    pip3 install gcovr
    gcovr --root . --xml -o coverage.xml
fi

# Generate compilation database
echo "Generating compilation database..."
if command -v bear &> /dev/null; then
    bear -- g++ -std=c++17 -c User.cpp Customer.cpp DeliveryDriver.cpp main.cpp
else
    echo "bear not found. Installing..."
    brew install bear
    bear -- g++ -std=c++17 -c User.cpp Customer.cpp DeliveryDriver.cpp main.cpp
fi

# Run SonarScanner
echo "Running SonarScanner..."
if [ -f compile_commands.json ]; then
    /opt/homebrew/bin/sonar-scanner \
        -Dsonar.token=6ffccf5176f47d66e243063b34d92d681c11df80
else
    echo "Error: compile_commands.json not generated!"
    exit 1
fi

echo "========================================="
echo "  Analysis Complete!"
echo "  Coverage report: coverage.xml"
echo "  HTML report: coverage.html"
echo "  SonarCloud Dashboard: https://sonarcloud.io/dashboard?id=anas4208-workspace_anas4208-workspace"
echo "========================================="