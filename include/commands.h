#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "parser.h"

namespace commands {
    // TODO: these handlers are placeholders. Implement logic in separate modules.
    void handle_load(const Command& cmd);
    void handle_select(const Command& cmd);
    void handle_insert(const Command& cmd);
    void handle_unknown(const Command& cmd);
}

#endif // COMMANDS_H
