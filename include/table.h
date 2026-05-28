#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <algorithm>

struct Table {
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> rows;

    void clear() {
        name.clear();
        columns.clear();
        rows.clear();
    }

    size_t nrows() const { return rows.size(); }
    size_t ncols() const { return columns.size(); }

    int column_index(const std::string& col) const {
        auto it = std::find(columns.begin(), columns.end(), col);
        if (it == columns.end()) return -1;
        return static_cast<int>(std::distance(columns.begin(), it));
    }
    // Legacy / convenience names used by tests
    size_t row_count() const { return nrows(); }
    size_t column_count() const { return ncols(); }
};

#endif // TABLE_H
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
