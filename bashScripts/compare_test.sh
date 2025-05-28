#!/bin/bash

# Define paths relative to script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
TEST_FILE="$PROJECT_ROOT/build/Release/test.csv"
EMOTIBIT_DIR="/e"  # E drive mount point (adjust if needed for your system)

# Function to extract date from filename
extract_date_from_filename() {
    local filename="$1"
    # Extract date pattern like 2025-05-23_15-31-07-786432 from filename
    if [[ $filename =~ ([0-9]{4}-[0-9]{2}-[0-9]{2}_[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{6}) ]]; then
        echo "${BASH_REMATCH[1]}"
    elif [[ $filename =~ ([0-9]{4}-[0-9]{2}-[0-9]{2}_[0-9]{2}-[0-9]{2}-[0-9]{2}) ]]; then
        # Fallback for shorter format without microseconds
        echo "${BASH_REMATCH[1]}-000000"
    else
        echo "0000-01-01_00-00-00-000000"  # Default for non-matching files
    fi
}

# Function to convert date format to comparable format
date_to_comparable() {
    local date_str="$1"
    # Convert 2025-05-23_15-31-07-786432 to 20250523153107786432 for easy comparison
    echo "${date_str//[-_]/}"
}

# Function to find the most recent CSV file based on filename date
find_most_recent_csv() {
    local most_recent_file=""
    local most_recent_date="00000000000000000000"
    
    echo "Searching for CSV files in $EMOTIBIT_DIR..." >&2
    
    # Find all CSV files that are NOT _info files
    while IFS= read -r -d '' file; do
        local basename=$(basename "$file")
        
        # Skip _info files
        if [[ "$basename" == *"_info.csv" ]]; then
            continue
        fi
        
        local file_date=$(extract_date_from_filename "$basename")
        local comparable_date=$(date_to_comparable "$file_date")
        
        echo "Found: $basename (date: $file_date)" >&2
        
        if [[ "$comparable_date" > "$most_recent_date" ]]; then
            most_recent_date="$comparable_date"
            most_recent_file="$file"
        fi
    done < <(find "$EMOTIBIT_DIR" -name "*.csv" -type f -print0 2>/dev/null)
    
    echo "$most_recent_file"
}

# Function to generate test file if it doesn't exist
generate_test_file() {
    echo "Test file not found. Generating it using EmotiBitDataTester..."
    
    # Check if we're in the right directory structure
    if [[ ! -f "$PROJECT_ROOT/src/EmotiBitDataTester.cpp" ]]; then
        echo "Error: EmotiBitDataTester.cpp not found at $PROJECT_ROOT/src/EmotiBitDataTester.cpp"
        echo "Make sure you're running this script from the correct location."
        return 1
    fi
    
    # Build and run the data tester
    cd "$PROJECT_ROOT"
    
    # Try to build with different methods
    if command -v cmake >/dev/null 2>&1 && [[ -f "CMakeLists.txt" ]]; then
        echo "Building with CMake..."
        mkdir -p build
        cd build
        cmake .. && make EmotiBitDataTester
        if [[ -f "./EmotiBitDataTester" ]]; then
            ./EmotiBitDataTester
        else
            echo "Error: Failed to build EmotiBitDataTester with CMake"
            return 1
        fi
    elif command -v g++ >/dev/null 2>&1; then
        echo "Building with g++..."
        g++ -std=c++11 -I src src/EmotiBitDataTester.cpp src/EmotiBitPacket.cpp -o EmotiBitDataTester
        if [[ -f "./EmotiBitDataTester" ]]; then
            ./EmotiBitDataTester
        else
            echo "Error: Failed to build EmotiBitDataTester with g++"
            return 1
        fi
    else
        echo "Error: No suitable compiler found (cmake/make or g++)"
        return 1
    fi
    
    # Check if test.csv was generated
    if [[ -f "$TEST_FILE" ]]; then
        echo "✅ Test file generated successfully!"
        return 0
    else
        echo "❌ Failed to generate test file"
        return 1
    fi
}

# Main script
main() {
    echo "=== EmotiBit CSV Test Data Comparison Script ==="
    echo "Script location: $SCRIPT_DIR"
    echo "Project root: $PROJECT_ROOT"
    echo
    
    # Check if test file exists, if not try to generate it
    if [[ ! -f "$TEST_FILE" ]]; then
        echo "Test file not found at $TEST_FILE"
        read -p "Would you like to generate it? (y/n): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            if ! generate_test_file; then
                exit 1
            fi
        else
            echo "Error: Test file is required for comparison"
            exit 1
        fi
    fi
    
    # Check if E drive is accessible
    if [[ ! -d "$EMOTIBIT_DIR" ]]; then
        echo "Error: E drive not accessible at $EMOTIBIT_DIR"
        echo "Make sure the EmotiBit SD card is mounted"
        echo
        echo "Common mount points to try:"
        echo "  Windows Git Bash: /e"
        echo "  WSL: /mnt/e"
        echo "  Linux: /media/*/EMOTIBIT or /mnt/emotibit"
        echo
        read -p "Enter alternative path to EmotiBit SD card (or press Enter to exit): " alt_path
        if [[ -n "$alt_path" && -d "$alt_path" ]]; then
            EMOTIBIT_DIR="$alt_path"
        else
            exit 1
        fi
    fi
    
    # Find most recent CSV file
    echo "Finding most recent CSV file..."
    MOST_RECENT_CSV=$(find_most_recent_csv)
    
    if [[ -z "$MOST_RECENT_CSV" ]]; then
        echo "Error: No CSV files found in $EMOTIBIT_DIR"
        echo "Note: Looking for files like '2025-05-23_15-31-07-786432.csv' (excluding '_info.csv' files)"
        exit 1
    fi
    
    echo
    echo "Most recent CSV file: $(basename "$MOST_RECENT_CSV")"
    echo "Full path: $MOST_RECENT_CSV"
    if [[ -n "$INFO_FILE" ]]; then
        echo "Corresponding info file: $(basename "$INFO_FILE")"
    else
        echo "⚠️  No corresponding info file found"
    fi
    echo "Test file: $(basename "$TEST_FILE")"
    echo
    
    # Extract first few lines from each file for preview
    echo "=== TEST FILE ==="
    head -5 "$TEST_FILE" 2>/dev/null || echo "Error reading test file"
    
    echo
    echo "=== MOST RECENT CSV ==="
    head -5 "$MOST_RECENT_CSV" 2>/dev/null || echo "Error reading CSV file"
    
    if [[ -n "$INFO_FILE" ]]; then
        echo
        echo "=== INFO FILE (first 5 lines) ==="
        head -5 "$INFO_FILE" 2>/dev/null || echo "Error reading info file"
    fi
    
    echo
    echo "=== TEST DATA COMPARISON ==="
    
    # Create temporary files for comparison
    TEMP_TEST=$(mktemp)
    TEMP_CSV=$(mktemp)
    
    # Compare the entire files line by line
    if diff -q "$TEST_FILE" "$MOST_RECENT_CSV" >/dev/null 2>&1; then
        echo "✅ Files MATCH completely!"
    else
        echo "❌ Files DIFFER!"
        echo
        echo "=== FILE STATISTICS ==="
        TEST_LINES=$(wc -l < "$TEST_FILE")
        CSV_LINES=$(wc -l < "$MOST_RECENT_CSV")
        echo "Test file (baseline): $TEST_LINES lines"
        echo "EmotiBit CSV file: $CSV_LINES lines"
        echo
        
        if [[ $CSV_LINES -lt $TEST_LINES ]]; then
            echo "⚠️  EmotiBit CSV has fewer lines than expected"
            echo "   Missing $(($TEST_LINES - $CSV_LINES)) lines"
        elif [[ $CSV_LINES -gt $TEST_LINES ]]; then
            echo "⚠️  EmotiBit CSV has more lines than expected"
            echo "   Extra $(($CSV_LINES - $TEST_LINES)) lines"
        fi
        echo
        
        echo "=== LINE-BY-LINE COMPARISON ==="
        echo "Showing first 10 differences..."
        
        # Compare line by line and show differences
        diff --side-by-side --left-column "$TEST_FILE" "$MOST_RECENT_CSV" | head -10
        
        echo
        echo "=== DETAILED ANALYSIS ==="
        
        # Check if first lines match (header format)
        TEMP_TEST=$(mktemp)
        TEMP_CSV=$(mktemp)
        head -1 "$TEST_FILE" > "$TEMP_TEST"
        head -1 "$MOST_RECENT_CSV" > "$TEMP_CSV"
        
        if diff -q "$TEMP_TEST" "$TEMP_CSV" >/dev/null 2>&1; then
            echo "✅ Header format matches"
        else
            echo "❌ Header format differs"
            echo "Expected: $(cat "$TEMP_TEST")"
            echo "Actual:   $(cat "$TEMP_CSV")"
        fi
        
        # Show which lines differ
        echo
        echo "Lines that differ:"
        diff --unchanged-line-format="" --old-line-format="Expected line %dn: %L" --new-line-format="Actual line   %dn: %L" "$TEST_FILE" "$MOST_RECENT_CSV" | head -20
        
        # Cleanup
        rm -f "$TEMP_TEST" "$TEMP_CSV"
    fi    
}

# Run the script
main "$@"