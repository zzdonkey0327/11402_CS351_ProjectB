#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

enum class CommandType { LOAD, SELECT, INSERT, EXIT, UNKNOWN };

struct Command {
    CommandType type;
    std::string raw;   // 原始輸入
    std::string name;  // 指令名稱（首字）
    std::vector<std::string> args; // 其餘參數或原始參數字串
};

inline static std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// 簡單解析：只辨識首個 token 作為指令，並把其餘整段視為參數（不做深入 SQL 解析）
inline static Command parse_command(const std::string& line) {
    Command cmd{CommandType::UNKNOWN, line, "", {}};
    std::istringstream iss(line);
    std::string word;
    if (!(iss >> word)) return cmd;
    std::string uw = to_upper(word);
    if (uw == "LOAD") cmd.type = CommandType::LOAD;
    else if (uw == "SELECT") cmd.type = CommandType::SELECT;
    else if (uw == "INSERT") cmd.type = CommandType::INSERT;
    else if (uw == "EXIT" || uw == "QUIT") cmd.type = CommandType::EXIT;
    else cmd.type = CommandType::UNKNOWN;
    cmd.name = word;
    std::string rest;
    std::getline(iss, rest);
    // trim leading spaces
    if (!rest.empty()) {
        size_t pos = rest.find_first_not_of(' ');
        if (pos != std::string::npos) rest.erase(0, pos);
    }
    if (!rest.empty()) cmd.args.push_back(rest);
    return cmd;
}

#endif // PARSER_H
