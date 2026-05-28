// Minimal CLI skeleton for CSV mini-database
// Responsibilities:
// - Print welcome and supported commands
// - Read user input loop
// - Dispatch to placeholder handlers for LOAD / SELECT / INSERT
//
// Next tasks (TODOs):
// - Move parsing into a more robust parser module (include/parser.h exists)
// - Implement CSV loader and storage modules and connect to `commands` handlers
// - Add unit tests under `tests/` for LOAD behavior

#include <iostream>
#include <string>
#include "../include/parser.h"
#include "../include/commands.h"

static void print_welcome() {
	std::cout << "CSV Mini Database - v1\n";
	std::cout << "Supported commands:\n";
	std::cout << "  LOAD <file.csv>\n";
	std::cout << "  SELECT * FROM <table>    (projection support planned)\n";
	std::cout << "  INSERT INTO <table> (...) VALUES (...)\n";
	std::cout << "  EXIT  (or QUIT)\n";
	std::cout << "Type a command and press Enter.\n";
}

int main(int argc, char** argv) {
	print_welcome();

	std::string line;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, line)) break; // EOF
		// basic trim (leading/trailing)
		size_t first = line.find_first_not_of(' ');
		if (first == std::string::npos) continue; // empty line
		size_t last = line.find_last_not_of(' ');
		std::string trimmed = line.substr(first, last - first + 1);

		Command cmd = parse_command(trimmed);
		switch (cmd.type) {
			case CommandType::LOAD:
				commands::handle_load(cmd);
				break;
			case CommandType::SELECT:
				commands::handle_select(cmd);
				break;
			case CommandType::INSERT:
				commands::handle_insert(cmd);
				break;
			case CommandType::EXIT:
				std::cout << "Exiting.\n";
				return 0;
			default:
				commands::handle_unknown(cmd);
				break;
		}
	}

	return 0;
}
