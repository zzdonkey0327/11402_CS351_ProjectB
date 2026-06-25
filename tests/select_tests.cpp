#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/loader.h"
#include "../include/query.h"

namespace {

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}

std::vector<std::string> split_lines(const std::string& text) {
    std::vector<std::string> lines;
    std::stringstream stream(text);
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool is_separator_line(const std::string& line) {
    if (line.empty()) {
        return false;
    }

    for (char ch : line) {
        if (ch != '-' && ch != '+') {
            return false;
        }
    }
    return true;
}

Storage load_students_or_fail() {
    Storage storage;
    LoadError result = load_csv("tests/data/students.csv", storage);
    check(result.ok(), "setup should load students.csv successfully");
    return storage;
}

// TC-SELECT-01: Select All Columns
void test_TC_SELECT_01_select_all_columns() {
    std::cerr << "Running TC-SELECT-01: select all columns...\n";
    Storage storage = load_students_or_fail();

    SelectQuery query;
    std::string error_message;
    bool parsed = parse_select_query("* FROM students", query, error_message);
    check(parsed, "SELECT * query should parse successfully");

    std::string output;
    bool executed = parsed && execute_select(storage, query, output, error_message);
    check(executed, "SELECT * query should execute successfully");
    if (executed) {
        const std::vector<std::string> lines = split_lines(output);
        check(lines.size() == 5, "SELECT * output should contain header, separator, and three data rows");
        if (lines.size() == 5) {
            check(lines[0] == "id | name  | score | grade", "SELECT * header should be rendered in tabular format");
            check(is_separator_line(lines[1]), "SELECT * output should include a separator line");
            check(lines[2] == "1  | Alice | 90    | 3    ", "first SELECT * row should be aligned in table format");
            check(lines[3] == "2  | Bob   | 75    | 2    ", "second SELECT * row should be aligned in table format");
            check(lines[4] == "3  | Carol | 88    | 3    ", "third SELECT * row should be aligned in table format");
        }
    }
}

// TC-SELECT-02: Select Specific Columns
void test_TC_SELECT_02_select_specific_columns() {
    std::cerr << "Running TC-SELECT-02: select specific columns...\n";
    Storage storage = load_students_or_fail();

    SelectQuery query;
    std::string error_message;
    bool parsed = parse_select_query("name, score FROM students", query, error_message);
    check(parsed, "projection query should parse successfully");

    std::string output;
    bool executed = parsed && execute_select(storage, query, output, error_message);
    check(executed, "projection query should execute successfully");
    if (executed) {
        const std::vector<std::string> lines = split_lines(output);
        check(lines.size() == 5, "projection output should contain header, separator, and three data rows");
        if (lines.size() == 5) {
            check(lines[0] == "name  | score", "projection header should be rendered in tabular format");
            check(is_separator_line(lines[1]), "projection output should include a separator line");
            check(lines[2] == "Alice | 90   ", "first projection row should contain requested columns only");
            check(lines[3] == "Bob   | 75   ", "second projection row should contain requested columns only");
            check(lines[4] == "Carol | 88   ", "third projection row should contain requested columns only");
        }
    }
}

// TC-SELECT-03: Select Non-Existing Column
void test_TC_SELECT_03_select_missing_column() {
    std::cerr << "Running TC-SELECT-03: select missing column...\n";
    Storage storage = load_students_or_fail();

    SelectQuery query;
    std::string error_message;
    bool parsed = parse_select_query("age FROM students", query, error_message);
    check(parsed, "missing-column query should still parse successfully");

    std::string output;
    bool executed = parsed && execute_select(storage, query, output, error_message);
    check(!executed, "missing-column query should fail during execution");
    if (!executed) {
        check(error_message == "Column does not exist: age",
            "missing-column query should report a clear column error");
    }
}

// TC-SELECT-04: Select Before Load
void test_TC_SELECT_04_select_before_load() {
    std::cerr << "Running TC-SELECT-04: select before load...\n";
    Storage storage;

    SelectQuery query;
    std::string error_message;
    bool parsed = parse_select_query("* FROM students", query, error_message);
    check(parsed, "query should parse even when no table is loaded");

    std::string output;
    bool executed = parsed && execute_select(storage, query, output, error_message);
    check(!executed, "SELECT should fail when no table is loaded");
    if (!executed) {
        check(error_message == "No table is currently loaded.",
            "no-table query should report that no table is loaded");
    }
}

} // namespace

int main() {
    test_TC_SELECT_01_select_all_columns();
    test_TC_SELECT_02_select_specific_columns();
    test_TC_SELECT_03_select_missing_column();
    test_TC_SELECT_04_select_before_load();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "All SELECT tests passed.\n";
    return EXIT_SUCCESS;
}