#include <iostream>

#include "../include/commands.h"
#include "../include/insert.h"
#include "../include/loader.h"
#include "../include/query.h"

namespace {

Storage& active_storage() {
    static Storage storage;
    return storage;
}

std::string unwrap_path(std::string path) {
    if (path.size() >= 2) {
        const char first = path.front();
        const char last = path.back();
        if ((first == '"' && last == '"') || (first == '\'' && last == '\'')) {
            return path.substr(1, path.size() - 2);
        }
    }
    return path;
}

} // namespace

namespace commands {

void handle_load(const Command& cmd) {
    if (cmd.args.empty() || cmd.args[0].empty()) {
        std::cout << "LOAD requires a CSV file path.\n";
        return;
    }

    const std::string file_path = unwrap_path(cmd.args[0]);
    LoadError result = load_csv(file_path, active_storage());
    if (!result.ok()) {
        std::cout << result.message << "\n";
        return;
    }

    const Table& table = active_storage().current_table();
    std::cout << "Loaded table '" << table.name << "' from '" << file_path << "'";
    std::cout << " (" << table.column_count() << " columns, " << table.row_count() << " rows).\n";
}

void handle_select(const Command& cmd) {
    if (cmd.args.empty() || cmd.args[0].empty()) {
        std::cout << "Invalid SELECT syntax. Usage: SELECT * FROM <table> or SELECT col1, col2 FROM <table>\n";
        return;
    }

    SelectQuery query;
    std::string error_message;
    if (!parse_select_query(cmd.args[0], query, error_message)) {
        std::cout << error_message << "\n";
        return;
    }

    std::string output;
    if (!execute_select(active_storage(), query, output, error_message)) {
        std::cout << error_message << "\n";
        return;
    }

    std::cout << output;
}

void handle_insert(const Command& cmd) {
    if (cmd.args.empty() || cmd.args[0].empty()) {
        std::cout << "Invalid INSERT syntax. Usage: INSERT INTO <table> (col1, col2) VALUES (val1, val2)\n";
        return;
    }

    InsertQuery query;
    std::string error_message;
    if (!parse_insert_query(cmd.args[0], query, error_message)) {
        std::cout << error_message << "\n";
        return;
    }

    std::string success_message;
    if (!execute_insert(active_storage(), query, success_message, error_message)) {
        std::cout << error_message << "\n";
        return;
    }

    std::cout << success_message << "\n";
}

void handle_unknown(const Command& cmd) {
    std::cout << "Unrecognized or unsupported command: " << cmd.raw << "\n";
}

} // namespace commands
