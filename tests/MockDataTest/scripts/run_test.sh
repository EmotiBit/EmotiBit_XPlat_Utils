#!/bin/bash
set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build"
cmake ..
cmake --build . --config Release

EXECUTABLE="$PROJECT_ROOT/build/Release/MockDataTest.exe"

if [[ ! -f "$EXECUTABLE" ]]; then
    echo "Executable not found: $EXECUTABLE"
    exit 1
fi

TEST_FILE="$PROJECT_ROOT/build/Release/test.csv"
EMOTIBIT_CSV=""

if [[ ! -x "$PROJECT_ROOT/build/Release/MockDataTest" ]]; then
    echo "Executable not found or not executable: $PROJECT_ROOT/build/Release/MockDataTest"
    exit 1
fi

# Parse required -e or --extension argument
while [[ $# -gt 0 ]]; do
    case "$1" in
        -e|--extension)
            EMOTIBIT_CSV="$2"
            shift 2
            ;;
        *)
            echo "Usage: $0 -e|--extension <emotibit_csv_path>"
            exit 1
            ;;
    esac
done

if [[ -z "$EMOTIBIT_CSV" ]]; then
    echo "Error: You must specify -e or --extension <emotibit_csv_path>"
    exit 1
fi

if [[ ! -f "$TEST_FILE" ]]; then
    echo "Test file not found: $TEST_FILE"
    exit 1
fi

if [[ ! -f "$EMOTIBIT_CSV" ]]; then
    echo "EmotiBit CSV file not found: $EMOTIBIT_CSV"
    exit 1
fi

if diff -q "$TEST_FILE" "$EMOTIBIT_CSV" >/dev/null 2>&1; then
    echo "Files MATCH"
    exit 0
else
    echo "Files DIFFER"
    exit 1
fi