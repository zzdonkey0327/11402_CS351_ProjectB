#include "../include/insert.h"

#include <cctype>
#include <sstream>

namespace {

std::string trim_copy(const std::string& text) {
    std::size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start]))) {
        ++start;
    }

    std::size_t end = text.size();
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1]))) {
        --end;
    }

    return text.substr(start, end - start);
}

std::string to_upper_copy(std::string text) {
    for (char& ch : text) {
        ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }
    return text;
}

std::vector<std::string> split_list(const std::string& text) {
    std::vector<std::string> items;
    std::stringstream stream(text);
    std::string item;
    while (std::getline(stream, item, ',')) {
        items.push_back(trim_copy(item));
    }
    return items;
}

bool parse_parenthesized_list(
    const std::string& text,
    std::size_t open_pos,
    std::size_t close_pos,
    std::vector<std::string>& items,
    std::string& error_message,
    const std::string& label) {
    if (open_pos == std::string::npos || close_pos == std::string::npos || close_pos <= open_pos) {
        error_message = "Invalid INSERT syntax. Missing " + label + " list.";
        return false;
    }

    const std::string inner = trim_copy(text.substr(open_pos + 1, close_pos - open_pos - 1));
    items = split_list(inner);
    if (items.empty()) {
        error_message = "Invalid INSERT syntax. " + label + " list is empty.";
        return false;
    }

    for (const std::string& item : items) {
        if (item.empty()) {
            error_message = "Invalid INSERT syntax. " + label + " list contains an empty item.";
            return false;
        }
    }

    return true;
}

} // namespace

bool parse_insert_query(const std::string& text, InsertQuery& query, std::string& error_message) {
    query = InsertQuery{};
    error_message.clear();

    const std::string trimmed = trim_copy(text);
    if (trimmed.empty()) {
        error_message = "Invalid INSERT syntax. Usage: INSERT INTO <table> (col1, col2) VALUES (val1, val2)";
        return false;
    }

    const std::string upper = to_upper_copy(trimmed);
    if (upper.rfind("INTO ", 0) != 0) {
        error_message = "Invalid INSERT syntax. Missing INTO clause.";
        return false;
    }

    const std::size_t first_open = trimmed.find('(');
    if (first_open == std::string::npos) {
        error_message = "Invalid INSERT syntax. Missing column list.";
        return false;
    }

    query.table_name = trim_copy(trimmed.substr(5, first_open - 5));
    if (query.table_name.empty()) {
        error_message = "Invalid INSERT syntax. Missing table name.";
        return false;
    }

    const std::size_t first_close = trimmed.find(')', first_open);
    if (!parse_parenthesized_list(trimmed, first_open, first_close, query.columns, error_message, "column")) {
        return false;
    }

    const std::size_t values_pos = upper.find(" VALUES ", first_close == std::string::npos ? 0 : first_close);
    if (values_pos == std::string::npos) {
        error_message = "Invalid INSERT syntax. Missing VALUES clause.";
        return false;
    }

    const std::size_t second_open = trimmed.find('(', values_pos);
    const std::size_t second_close = trimmed.find(')', second_open);
    if (!parse_parenthesized_list(trimmed, second_open, second_close, query.values, error_message, "value")) {
        return false;
    }

    const std::string tail = trim_copy(trimmed.substr(second_close + 1));
    if (!tail.empty()) {
        error_message = "Invalid INSERT syntax. Unexpected trailing content.";
        return false;
    }

    return true;
}

bool execute_insert(Storage& storage, const InsertQuery& query, std::string& success_message, std::string& error_message) {
    success_message.clear();
    error_message.clear();

    if (!storage.has_table()) {
        error_message = "No table is currently loaded.";
        return false;
    }

    Table& table = storage.current_table();
    if (table.name != query.table_name) {
        error_message = "Table does not exist: " + query.table_name;
        return false;
    }

    if (query.columns.size() != query.values.size()) {
        error_message = "Value count does not match column count.";
        return false;
    }

    std::vector<std::string> new_row(table.column_count());
    std::vector<bool> assigned(table.column_count(), false);

    for (std::size_t i = 0; i < query.columns.size(); ++i) {
        const int column_index = table.column_index(query.columns[i]);
        if (column_index < 0) {
            error_message = "Column does not exist: " + query.columns[i];
            return false;
        }

        const std::size_t index = static_cast<std::size_t>(column_index);
        if (assigned[index]) {
            error_message = "Duplicate column in INSERT: " + query.columns[i];
            return false;
        }

        new_row[index] = query.values[i];
        assigned[index] = true;
    }

    for (bool present : assigned) {
        if (!present) {
            error_message = "INSERT must provide values for all table columns.";
            return false;
        }
    }

    table.rows.push_back(new_row);
    success_message = "Insert successful.";
    return true;
}