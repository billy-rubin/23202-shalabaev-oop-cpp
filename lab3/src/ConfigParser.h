#ifndef LAB3_CONFIGPARSER_H
#define LAB3_CONFIGPARSER_H
#include <string>
#include <vector>
#include <memory>
#include "converterfactory.h"

class ConfigParser {
private:
    std::vector<std::string> lines;
    const ConverterFactory& factory;
public:
    ConfigParser(const std::string& filename, const ConverterFactory& factory);
    std::vector<Converter*> parse() const;
};

#endif //LAB3_CONFIGPARSER_H
