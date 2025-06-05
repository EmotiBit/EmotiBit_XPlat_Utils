SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
TEST_FILE="$PROJECT_ROOT/build/Release/test.csv"

if grep -q '1' "$TEST_FILE"; then
    echo "Testing failed."
    exit 1
else
    echo "All tests passed."
    exit 0
fi