#ifndef ERROR_H
#define ERROR_H

#include <string>

enum class LoadErrorCode {
    None,
    FileOpenFailed,
    EmptyFile,
    MalformedHeader,
    MalformedRow
};

struct LoadError {
    LoadErrorCode code = LoadErrorCode::None;
    std::string message;

    bool ok() const;
};

std::string load_error_message(LoadErrorCode code, const std::string& file_path, std::size_t line_number = 0);

#endif // ERROR_H
