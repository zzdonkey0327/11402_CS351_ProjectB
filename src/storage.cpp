#include "../include/storage.h"

bool Storage::has_table() const {
    return has_table_;
}

const Table& Storage::current_table() const {
    return table_;
}

Table& Storage::current_table() {
    return table_;
}

void Storage::set_table(const Table& table) {
    table_ = table;
    has_table_ = true;
}

void Storage::clear() {
    table_ = Table{};
    has_table_ = false;
}
