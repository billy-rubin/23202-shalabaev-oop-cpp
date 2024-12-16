#include "ConverterFactory.h"
#include "Converter.h"
#include "ExceptionsHandler.h"
#include <sstream>
#include <stdexcept>
#include <regex>

ConverterFactory::ConverterFactory() {
    converterTypes["mute"] = new MuteConverter(0, 0);
    converterTypes["mix"] = new MixConverter(1, 0);
    converterTypes["echo"] = new EchoConverter(1, 0.5f);
}

ConverterFactory::~ConverterFactory() {
    for (auto &kv : converterTypes) {
        delete kv.second;
    }
}

Converter* ConverterFactory::createFromLine(const std::string& line) const {
    std::regex muteRegex("^mute\\s+(\\d+)\\s+(\\d+)$");
    std::regex mixRegex("^mix\\s+\\$(\\d+)(?:\\s+(\\d+))?$");
    std::regex echoRegex("^echo\\s+(\\d+)\\s+([0-9\\.]+)$");

    std::smatch match;

    // Check for commas and empty lines
    std::string trimmed = line;
    while(!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\t'))
        trimmed.pop_back();
    if (trimmed.empty() || trimmed[0] == '#') {
        return nullptr;
    }

    if (std::regex_match(trimmed, match, muteRegex)) {
        int startSec = std::stoi(match[1].str());
        int endSec = std::stoi(match[2].str());
        return new MuteConverter(startSec, endSec);
    } else if (std::regex_match(trimmed, match, mixRegex)) {
        int fileIndex = std::stoi(match[1].str());
        int insertSec = 0;
        if (match[2].matched) {
            insertSec = std::stoi(match[2].str());
        }
        return new MixConverter(fileIndex, insertSec);
    } else if (std::regex_match(trimmed, match, echoRegex)) {
        int delaySec = std::stoi(match[1].str());
        float attenuation = std::stof(match[2].str());
        return new EchoConverter(delaySec, attenuation);
    } else {
        throw ConfigParseException("Unknown or invalid converter line: " + line);
    }
}