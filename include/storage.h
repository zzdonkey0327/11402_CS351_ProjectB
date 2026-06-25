#ifndef STORAGE_H
#define STORAGE_H

#include "table.h"

class Storage {
public:
    bool has_table() const;
    const Table& current_table() const;
    Table& current_table();
    void set_table(const Table& table);
    void clear();

private:
    bool has_table_ = false;
    Table table_;
};

#endif // STORAGE_H
