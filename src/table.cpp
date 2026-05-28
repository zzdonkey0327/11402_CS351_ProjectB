#include "../include/table.h"

#include <algorithm>

bool Table::empty() const {
    return columns.empty() && rows.empty();
}

std::size_t Table::column_count() const {
    return columns.size();
}

std::size_t Table::row_count() const {
    return rows.size();
}

int Table::column_index(const std::string& column_name) const {
    for (std::size_t i = 0; i < columns.size(); ++i) {
        if (columns[i] == column_name) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
