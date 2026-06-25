#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>

#include "storage.h"

struct SelectQuery {
    bool select_all = false;
    std::vector<std::string> columns;
    std::string table_name;
};

bool parse_select_query(const std::string& text, SelectQuery& query, std::string& error_message);
bool execute_select(const Storage& storage, const SelectQuery& query, std::string& output, std::string& error_message);

#endif // QUERY_H