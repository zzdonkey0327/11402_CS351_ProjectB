#include <cstdlib>
#include <iostream>
#include <string>

#include "../include/loader.h"

namespace {

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}

// TC-LOAD-01: Load Valid CSV File
void test_TC_LOAD_01_valid_csv() {
    Storage storage;
    std::cerr << "Running TC-LOAD-01: valid CSV load...\n";
    LoadError result = load_csv("tests/data/students.csv", storage);

    check(result.ok(), "valid CSV should load successfully");
    check(storage.has_table(), "storage should contain an active table after load");

    if (storage.has_table()) {
        const Table& table = storage.current_table();
        check(table.name == "students", "table name should be derived from file name");
        check(table.column_count() == 4, "valid CSV should expose four columns");
        check(table.row_count() == 3, "valid CSV should expose three rows");
        check(table.columns.size() == 4 && table.columns[0] == "id" && table.columns[1] == "name" && table.columns[2] == "score" && table.columns[3] == "grade",
            "header row should be parsed as column names");
        check(table.rows.size() == 3 && table.rows[0][1] == "Alice" && table.rows[2][2] == "88" && table.rows[1][3] == "2",
            "data rows should be parsed correctly");
    }
}

// TC-LOAD-02: Load Missing File
void test_TC_LOAD_02_missing_file() {
    Storage storage;
    std::cerr << "Running TC-LOAD-02: missing file load...\n";
    LoadError result = load_csv("tests/data/missing.csv", storage);

    check(!result.ok(), "missing file should fail");
    check(result.code == LoadErrorCode::FileOpenFailed, "missing file should report FileOpenFailed");
    check(!storage.has_table(), "storage should remain empty after failed load");
}

// TC-LOAD-03: Load Malformed CSV File
void test_TC_LOAD_03_malformed_csv() {
    Storage storage;
    std::cerr << "Running TC-LOAD-03: malformed CSV load...\n";
    LoadError result = load_csv("tests/data/students_malformed.csv", storage);

    check(!result.ok(), "malformed CSV should fail");
    check(result.code == LoadErrorCode::MalformedRow, "malformed CSV should report MalformedRow");
    check(!storage.has_table(), "storage should remain empty after malformed CSV load");
}

} // namespace

int main() {
    test_TC_LOAD_01_valid_csv();
    test_TC_LOAD_02_missing_file();
    test_TC_LOAD_03_malformed_csv();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "All LOAD tests passed.\n";
    return EXIT_SUCCESS;
}
