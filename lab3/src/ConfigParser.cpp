#include "ConfigParser.h"
#include <fstream>
#include "ExceptionsHandler.h"
ConfigParser::ConfigParser(const std::string& filename, const ConverterFactory& factory)
        : factory(factory) {
    std::ifstream in(filename);

    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
}

std::vector<Converter*> ConfigParser::parse() const {
    std::vector<Converter*> converters;
    for (auto &line : lines) {
        Converter* c = factory.createFromLine(line);
        if (c) {
            converters.push_back(c);
        }
    }
    return converters;
}