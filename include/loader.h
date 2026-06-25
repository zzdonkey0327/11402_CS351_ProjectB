#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "error.h"
#include "storage.h"

// Load a CSV file into the provided storage.
// Returns a LoadError describing success/failure.
LoadError load_csv(const std::string& file_path, Storage& storage);

#endif // LOADER_H
