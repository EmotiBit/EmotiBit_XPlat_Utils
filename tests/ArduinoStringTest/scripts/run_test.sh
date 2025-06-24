#!/bin/bash
set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build"
cmake ..
cmake --build . --config Release

EXECUTABLE="$PROJECT_ROOT/build/Release/ArduinoStringTest.exe"

if [[ ! -f "$EXECUTABLE" ]]; then
    echo "Executable not found: $EXECUTABLE"
    exit 1
fi

"$EXECUTABLE"
RESULT=$?

if [[ $RESULT -eq 0 ]]; then
    echo "BASH: All tests passed."
    exit 0
else
    echo "BASH: Some tests failed."
    exit 1
fi