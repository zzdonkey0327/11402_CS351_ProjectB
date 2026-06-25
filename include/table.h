#ifndef TABLE_H
#define TABLE_H

#include <cstddef>
#include <string>
#include <vector>

struct Table {
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> rows;

    bool empty() const;
    std::size_t column_count() const;
    std::size_t row_count() const;
    int column_index(const std::string& column_name) const;
};

#endif // TABLE_H
