#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/insert.h"
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

Storage load_students_or_fail() {
    Storage storage;
    LoadError result = load_csv("tests/data/students.csv", storage);
    check(result.ok(), "setup should load students.csv successfully");
    return storage;
}

// TC-INSERT-01: Insert Valid Row
void test_TC_INSERT_01_insert_valid_row() {
    std::cerr << "Running TC-INSERT-01: insert valid row...\n";
    Storage storage = load_students_or_fail();

    InsertQuery query;
    std::string error_message;
    bool parsed = parse_insert_query("INTO students (id, name, score, grade) VALUES (4, David, 92, 2)", query, error_message);
    check(parsed, "valid INSERT query should parse successfully");

    std::string success_message;
    bool executed = parsed && execute_insert(storage, query, success_message, error_message);
    check(executed, "valid INSERT query should execute successfully");
    if (executed) {
        check(success_message == "Insert successful.", "valid INSERT should report success");
        check(storage.current_table().row_count() == 4, "valid INSERT should append a fourth row");

        SelectQuery select_query;
        std::string select_error;
        bool select_parsed = parse_select_query("* FROM students", select_query, select_error);
        check(select_parsed, "SELECT setup after INSERT should parse successfully");

        std::string output;
        bool select_ok = select_parsed && execute_select(storage, select_query, output, select_error);
        check(select_ok, "SELECT after INSERT should execute successfully");
        if (select_ok) {
            check(output.find("4  | David | 92    | 2") != std::string::npos,
                "SELECT output should contain the inserted record");
        }
    }
}

// TC-INSERT-02: Insert With Mismatched Value Count
void test_TC_INSERT_02_mismatched_value_count() {
    std::cerr << "Running TC-INSERT-02: mismatched value count...\n";
    Storage storage = load_students_or_fail();

    InsertQuery query;
    std::string error_message;
    bool parsed = parse_insert_query("INTO students (id, name, score, grade) VALUES (5, Emma)", query, error_message);
    check(parsed, "mismatched-value INSERT should still parse successfully");

    std::string success_message;
    bool executed = parsed && execute_insert(storage, query, success_message, error_message);
    check(!executed, "mismatched-value INSERT should fail during execution");
    if (!executed) {
        check(error_message == "Value count does not match column count.",
            "mismatched-value INSERT should report a value count error");
        check(storage.current_table().row_count() == 3, "failed INSERT should not modify row count");
    }
}

// TC-INSERT-03: Insert With Invalid Column Name
void test_TC_INSERT_03_invalid_column_name() {
    std::cerr << "Running TC-INSERT-03: invalid column name...\n";
    Storage storage = load_students_or_fail();

    InsertQuery query;
    std::string error_message;
    bool parsed = parse_insert_query("INTO students (id, fullname, score, grade) VALUES (5, Emma, 81, 2)", query, error_message);
    check(parsed, "invalid-column INSERT should still parse successfully");

    std::string success_message;
    bool executed = parsed && execute_insert(storage, query, success_message, error_message);
    check(!executed, "invalid-column INSERT should fail during execution");
    if (!executed) {
        check(error_message == "Column does not exist: fullname",
            "invalid-column INSERT should report a column error");
        check(storage.current_table().row_count() == 3, "failed INSERT should not modify row count");
    }
}

// TC-INSERT-04: Insert Before Load
void test_TC_INSERT_04_insert_before_load() {
    std::cerr << "Running TC-INSERT-04: insert before load...\n";
    Storage storage;

    InsertQuery query;
    std::string error_message;
    bool parsed = parse_insert_query("INTO students (id, name, score, grade) VALUES (4, David, 92, 2)", query, error_message);
    check(parsed, "INSERT should parse even when no table is loaded");

    std::string success_message;
    bool executed = parsed && execute_insert(storage, query, success_message, error_message);
    check(!executed, "INSERT should fail when no table is loaded");
    if (!executed) {
        check(error_message == "No table is currently loaded.",
            "insert-before-load should report that no table is loaded");
    }
}

} // namespace

int main() {
    test_TC_INSERT_01_insert_valid_row();
    test_TC_INSERT_02_mismatched_value_count();
    test_TC_INSERT_03_invalid_column_name();
    test_TC_INSERT_04_insert_before_load();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "All INSERT tests passed.\n";
    return EXIT_SUCCESS;
}