#include <iostream>

#include "../include/commands.h"
#include "../include/loader.h"

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
    std::cout << "[TODO] SELECT handler - implement query execution.\n";
    if (!cmd.args.empty()) std::cout << "  Args: " << cmd.args[0] << "\n";
}

void handle_insert(const Command& cmd) {
    std::cout << "[TODO] INSERT handler - implement insert logic.\n";
    if (!cmd.args.empty()) std::cout << "  Args: " << cmd.args[0] << "\n";
}

void handle_unknown(const Command& cmd) {
    std::cout << "Unrecognized or unsupported command: " << cmd.raw << "\n";
}

} // namespace commands
