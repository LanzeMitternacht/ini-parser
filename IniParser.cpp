#include "IniParser.h"
#include <fstream>

bool IniParser::isIniFile(const std::string& filepath) const {
    return filepath.size() > 4 && filepath.substr(filepath.size() - 4) == ".ini";
}

std::string IniParser::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

ParseResult IniParser::parseFile(const std::string& filepath) {
    if (!isIniFile(filepath)) {
        return { ParseResult::ERROR_FILE_TYPE, "File must have a .ini extension" };
    }

    std::ifstream file(filepath);
    if (!file.is_open()) {
        return { ParseResult::ERROR_READ_FILE, "File is not open" };
    }

    parseData.clear();
    std::string line, currentSection;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
            continue;
        }

        size_t posDelimiter = line.find('=');
        if (posDelimiter != std::string::npos) {
            std::string key = trim(line.substr(0, posDelimiter));
            std::string value = trim(line.substr(posDelimiter + 1));
            parseData[currentSection][key] = value;
        }
    }

    return { ParseResult::SUCCESS, "The parsing is finished" };
}

ParseResult IniParser::getValue(const std::string& section, const std::string& key, std::string& value) {
    auto sectionFind = parseData.find(section);
    if (sectionFind == parseData.end()) {
        return { ParseResult::ERROR_SECTION_NOT_FIND, "Section not found: " + section };
    }

    auto keyFind = sectionFind->second.find(key);
    if (keyFind == sectionFind->second.end()) {
        return { ParseResult::ERROR_KEY_NOT_FIND, "Key not found in " + section + " : " + key };
    }

    value = keyFind->second;
    return { ParseResult::SUCCESS, "Value found" };
}

DataMap& IniParser::getDataMap(){
    return parseData;
}
