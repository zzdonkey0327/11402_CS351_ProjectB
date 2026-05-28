#include <iostream>
#include "../include/commands.h"

namespace commands {

void handle_load(const Command& cmd) {
    std::cout << "[TODO] LOAD handler - implement CSV loading.\n";
    if (!cmd.args.empty()) std::cout << "  Args: " << cmd.args[0] << "\n";
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
