#include "../include/error.h"

bool LoadError::ok() const {
    return code == LoadErrorCode::None;
}

std::string load_error_message(LoadErrorCode code, const std::string& file_path, std::size_t line_number) {
    switch (code) {
        case LoadErrorCode::FileOpenFailed:
            return "Unable to open CSV file: " + file_path;
        case LoadErrorCode::EmptyFile:
            return "CSV file is empty: " + file_path;
        case LoadErrorCode::MalformedHeader:
            return "CSV header is malformed: " + file_path;
        case LoadErrorCode::MalformedRow:
            if (line_number > 0) {
                return "Malformed CSV row at line " + std::to_string(line_number) + ": " + file_path;
            }
            return "Malformed CSV row: " + file_path;
        case LoadErrorCode::None:
        default:
            return {};
    }
}
