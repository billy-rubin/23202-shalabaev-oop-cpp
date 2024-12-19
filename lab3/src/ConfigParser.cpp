#include "ConfigParser.h"
#include <fstream>
#include "ExceptionsHandler.h"

Converter* ConfigParser::getConverterType(std::string line) const {
    std::regex muteRegex("^mute\\s+(\\d+)\\s+(\\d+)$");
    std::regex mixRegex("^mix\\s+\\$(\\d+)(?:\\s+(\\d+))?$");
    std::regex echoRegex("^echo\\s+(\\d+)\\s+([0-9\\.]+)$");

    std::smatch match;
    std::string trimmed = line;
    while(!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\t'))
        trimmed.pop_back();

    if (trimmed.empty() || trimmed[0] == '#') {
        return nullptr;
    }
    if (std::regex_match(trimmed, match, muteRegex)){
        MuterFactory muter;
        Converter* conv = muter.create(match);
        return conv;
    } else if (std::regex_match(trimmed, match, mixRegex)){
        MixerFactory mixer;
        Converter* conv = mixer.create(match);
        return conv;
    } else if (std::regex_match(trimmed, match, echoRegex)){
        EchoerFactory echoer;
        Converter* conv = echoer.create(match);
        return conv;
    } else {
        throw ConfigParseException("Unknown or invalid converter line: " + line);
    }
}

ConfigParser::ConfigParser(const std::string& filename){
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
}

std::vector<Converter*> ConfigParser::parse() const {
    std::vector<Converter*> converters;
    for (auto &line : lines) {
        Converter* converter = getConverterType(line);
        if (converter == nullptr)
            continue;
        converters.push_back(converter);
        }
    return converters;
}