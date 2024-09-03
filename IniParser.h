#ifndef INIPARSER_H
#define INIPARSER_H

#include <string>
#include <unordered_map>

struct ParseResult {
    enum ErrorCode {
        SUCCESS = 0,
        ERROR_FILE_TYPE,
        ERROR_READ_FILE,
        ERROR_EMPTY_FILE,
        ERROR_SECTION_NOT_FIND,
        ERROR_KEY_NOT_FIND,
        ERROR_VALUE_NOT_FIND
    };

    ErrorCode errorCode;
    std::string errorMessage;

    bool isSuccess() const {
        return errorCode == SUCCESS;
    }
};

using DataMap = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

class IniParser {
public:
    ParseResult parseFile(const std::string& filepath);
    ParseResult getValue(const std::string& section, const std::string& key, std::string& value);
    DataMap& getDataMap();

private:
    mutable DataMap parseData;

    bool isIniFile(const std::string& filepath) const;
    std::string trim(const std::string& str) const;
};

#endif
