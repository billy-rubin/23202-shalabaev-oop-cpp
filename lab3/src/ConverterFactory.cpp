#include "ConverterFactory.h"

Converter* MuterFactory::create(const std::smatch& match) const {
    if (match.size() < 3) {
        throw ConfigParseException("Invalid parameters for mute converter.");
    }

    int startSec = std::stoi(match[1].str());
    int endSec = std::stoi(match[2].str());

    return new MuteConverter(startSec, endSec);
}

Converter* MixerFactory::create(const std::smatch& match) const {
    if (match.size() < 2) {
        throw ConfigParseException("Invalid parameters for mix converter.");
    }

    int fileIndex = std::stoi(match[1].str()) - 1;
    int insertSec = 0;
    if (match.size() >= 3 && match[2].matched) {
        insertSec = std::stoi(match[2].str());
    }

    return new MixConverter(fileIndex, insertSec);
}

Converter* EchoerFactory::create(const std::smatch& match) const {
    if (match.size() < 3) {
        throw ConfigParseException("Invalid parameters for echo converter.");
    }

    int startSec = std::stoi(match[1].str());
    float attenuation = std::stof(match[2].str());
    return new EchoConverter(startSec, attenuation);
}
