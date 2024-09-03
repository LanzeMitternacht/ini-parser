#include <iostream>
#include "IniParser.h"

int main() {
    IniParser parser;
    ParseResult result = parser.parseFile("testparsing.ini");

    if (result.isSuccess()) {
        std::cout << result.errorMessage << std::endl;

        DataMap& data = parser.getDataMap();
        for (const auto& section : data) {
            std::cout << "[" << section.first << "]" << std::endl;
            for (const auto& pair : section.second) {
                std::cout << pair.first << " = " << pair.second << std::endl;
            }
            std::cout << std::endl;
        }

        std::string section = "User";
        std::string key = "Name";
        std::string value;
        ParseResult valueResult = parser.getValue(section, key, value);
        if (valueResult.isSuccess()) {
            std::cout << "Value found for " << key << " in section " << section << " = " << value << std::endl;
        }
        else {
            std::cerr << "Error: " << valueResult.errorMessage << std::endl;
        }

    }
    else {
        std::cerr << "Error: " << result.errorMessage << std::endl;
    }

    return 0;
}
