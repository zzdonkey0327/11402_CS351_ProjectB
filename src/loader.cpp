#include "../include/loader.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

namespace {

std::string trim(const std::string& text) {
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

std::string strip_cr(std::string text) {
    if (!text.empty() && text.back() == '\r') {
        text.pop_back();
    }
    return text;
}

std::vector<std::string> split_csv_row(const std::string& row) {
    std::vector<std::string> cells;
    std::stringstream stream(row);
    std::string cell;
    while (std::getline(stream, cell, ',')) {
        cells.push_back(trim(strip_cr(cell)));
    }

    if (!row.empty() && row.back() == ',') {
        cells.push_back("");
    }

    return cells;
}

std::string derive_table_name(const std::string& file_path) {
    std::size_t slash_pos = file_path.find_last_of("/\\");
    std::string file_name = (slash_pos == std::string::npos) ? file_path : file_path.substr(slash_pos + 1);

    std::size_t dot_pos = file_name.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return file_name;
    }

    return file_name.substr(0, dot_pos);
}

LoadError make_error(LoadErrorCode code, const std::string& file_path, std::size_t line_number = 0) {
    return LoadError{code, load_error_message(code, file_path, line_number)};
}

} // namespace

LoadError load_csv(const std::string& file_path, Storage& storage) {
    std::ifstream input(file_path);
    if (!input.is_open()) {
        return make_error(LoadErrorCode::FileOpenFailed, file_path);
    }

    std::string header_line;
    if (!std::getline(input, header_line)) {
        return make_error(LoadErrorCode::EmptyFile, file_path);
    }

    header_line = strip_cr(header_line);
    std::vector<std::string> columns = split_csv_row(header_line);
    if (columns.empty() || (columns.size() == 1 && columns[0].empty())) {
        return make_error(LoadErrorCode::MalformedHeader, file_path);
    }

    Table table;
    table.name = derive_table_name(file_path);
    table.columns = columns;

    std::string row_line;
    std::size_t line_number = 1;
    while (std::getline(input, row_line)) {
        ++line_number;
        row_line = strip_cr(row_line);
        if (trim(row_line).empty()) {
            continue;
        }

        std::vector<std::string> cells = split_csv_row(row_line);
        if (cells.size() != table.columns.size()) {
            return make_error(LoadErrorCode::MalformedRow, file_path, line_number);
        }

        table.rows.push_back(cells);
    }

    storage.set_table(table);
    return LoadError{};
}
