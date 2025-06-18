#!/bin/bash
set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build/Release"
EXECUTABLE="$BUILD_DIR/ArduinoStringTest"

if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Executable not found or not executable: $EXECUTABLE"
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