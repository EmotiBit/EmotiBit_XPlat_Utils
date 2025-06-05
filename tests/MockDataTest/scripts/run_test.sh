#!/bin/bash
set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
TEST_FILE="$PROJECT_ROOT/build/Release/test.csv"

# Prompt user for CSV file path
read -p "Enter the path to the EmotiBit CSV file to compare: " EmotiBit_csv

if [[ ! -f "$TEST_FILE" ]]; then
    echo "Test file not found: $TEST_FILE"
    exit 1
fi

if [[ -z "$EmotiBit_csv" || ! -f "$EmotiBit_csv" ]]; then
    echo "CSV file not found at: $EmotiBit_csv"
    exit 1
fi

if diff -q "$TEST_FILE" "$EmotiBit_csv" >/dev/null 2>&1; then
    echo "Files MATCH"
    exit 0
else
    echo "Files DIFFER"
    exit 1
fi