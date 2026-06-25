#ifndef INSERT_H
#define INSERT_H

#include <string>
#include <vector>

#include "storage.h"

struct InsertQuery {
    std::string table_name;
    std::vector<std::string> columns;
    std::vector<std::string> values;
};

bool parse_insert_query(const std::string& text, InsertQuery& query, std::string& error_message);
bool execute_insert(Storage& storage, const InsertQuery& query, std::string& success_message, std::string& error_message);

#endif // INSERT_H