#include "../include/query.h"

#include <cctype>
#include <iomanip>
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

std::vector<std::string> split_columns(const std::string& text) {
    std::vector<std::string> columns;
    std::stringstream stream(text);
    std::string item;
    while (std::getline(stream, item, ',')) {
        columns.push_back(trim_copy(item));
    }
    return columns;
}

std::vector<std::size_t> compute_column_widths(
    const Table& table,
    const std::vector<std::string>& selected_names,
    const std::vector<int>& selected_indexes) {
    std::vector<std::size_t> widths(selected_names.size(), 0);

    for (std::size_t i = 0; i < selected_names.size(); ++i) {
        widths[i] = selected_names[i].size();
    }

    for (const std::vector<std::string>& row : table.rows) {
        for (std::size_t i = 0; i < selected_indexes.size(); ++i) {
            const std::size_t cell_index = static_cast<std::size_t>(selected_indexes[i]);
            if (cell_index < row.size() && row[cell_index].size() > widths[i]) {
                widths[i] = row[cell_index].size();
            }
        }
    }

    return widths;
}

void append_separator(std::ostringstream& output, const std::vector<std::size_t>& widths) {
    for (std::size_t i = 0; i < widths.size(); ++i) {
        if (i > 0) {
            output << "-+-";
        }
        output << std::string(widths[i], '-');
    }
    output << '\n';
}

void append_row(
    std::ostringstream& output,
    const std::vector<std::string>& cells,
    const std::vector<std::size_t>& widths) {
    for (std::size_t i = 0; i < cells.size(); ++i) {
        if (i > 0) {
            output << " | ";
        }
        output << std::left << std::setw(static_cast<int>(widths[i])) << cells[i];
    }
    output << '\n';
}

} // namespace

bool parse_select_query(const std::string& text, SelectQuery& query, std::string& error_message) {
    query = SelectQuery{};
    error_message.clear();

    const std::string trimmed = trim_copy(text);
    if (trimmed.empty()) {
        error_message = "Invalid SELECT syntax. Usage: SELECT * FROM <table> or SELECT col1, col2 FROM <table>";
        return false;
    }

    const std::string upper = to_upper_copy(trimmed);
    const std::size_t from_pos = upper.find(" FROM ");
    if (from_pos == std::string::npos) {
        error_message = "Invalid SELECT syntax. Missing FROM clause.";
        return false;
    }

    const std::string column_part = trim_copy(trimmed.substr(0, from_pos));
    const std::string table_part = trim_copy(trimmed.substr(from_pos + 6));

    if (column_part.empty() || table_part.empty()) {
        error_message = "Invalid SELECT syntax. Missing column list or table name.";
        return false;
    }

    query.table_name = table_part;
    if (column_part == "*") {
        query.select_all = true;
        return true;
    }

    query.columns = split_columns(column_part);
    if (query.columns.empty()) {
        error_message = "Invalid SELECT syntax. Column list is empty.";
        return false;
    }

    for (const std::string& column : query.columns) {
        if (column.empty()) {
            error_message = "Invalid SELECT syntax. Column list contains an empty column name.";
            return false;
        }
    }

    return true;
}

bool execute_select(const Storage& storage, const SelectQuery& query, std::string& output, std::string& error_message) {
    output.clear();
    error_message.clear();

    if (!storage.has_table()) {
        error_message = "No table is currently loaded.";
        return false;
    }

    const Table& table = storage.current_table();
    if (table.name != query.table_name) {
        error_message = "Table does not exist: " + query.table_name;
        return false;
    }

    std::vector<int> selected_indexes;
    std::vector<std::string> selected_names;

    if (query.select_all) {
        selected_names = table.columns;
        for (std::size_t i = 0; i < table.columns.size(); ++i) {
            selected_indexes.push_back(static_cast<int>(i));
        }
    } else {
        selected_names = query.columns;
        for (const std::string& column : query.columns) {
            const int index = table.column_index(column);
            if (index < 0) {
                error_message = "Column does not exist: " + column;
                return false;
            }
            selected_indexes.push_back(index);
        }
    }

    const std::vector<std::size_t> widths = compute_column_widths(table, selected_names, selected_indexes);

    std::ostringstream result;
    append_row(result, selected_names, widths);
    append_separator(result, widths);

    for (const std::vector<std::string>& row : table.rows) {
        std::vector<std::string> selected_cells;
        selected_cells.reserve(selected_indexes.size());
        for (int index : selected_indexes) {
            selected_cells.push_back(row[static_cast<std::size_t>(index)]);
        }
        append_row(result, selected_cells, widths);
    }

    output = result.str();
    return true;
}