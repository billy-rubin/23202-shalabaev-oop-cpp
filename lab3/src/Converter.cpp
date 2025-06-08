#include "Converter.h"

MuteConverter::MuteConverter(int startSec, int endSec)
        : start(startSec), end(endSec) {}

std::vector<int16_t> MuteConverter::convert(const std::vector<int16_t>& mainStream,
                                            const std::vector<WavFile*>& additionalInputs) const {
    std::vector<int16_t> outSamples = mainStream;

    int startIndex = start * sampleRate;
    int endIndex   = end * sampleRate;
    if (endIndex > outSamples.size()) {
        endIndex = outSamples.size();
    }
    if (startIndex < endIndex && startIndex < outSamples.size()) {
        std::fill(outSamples.begin() + startIndex,outSamples.begin() + endIndex,0);
    }

    return outSamples;
}

std::string MuteConverter::getDescription() const {
    return "mute <start_sec> <end_sec>\n"
           "Sets the audio samples between start_sec and end_sec to zero.\n";
}

MixConverter::MixConverter(int fileIndex, int insertSec)
        : fileIndex(fileIndex), insert(insertSec) {}

std::vector<int16_t> MixConverter::convert(const std::vector<int16_t>& mainStream,
                                           const std::vector<WavFile*>& additionalInputs) const {
    if (additionalInputs[fileIndex] == nullptr) {
        throw ConversionException("Mix: additional input not found for index " + std::to_string(fileIndex));
    }
    const WavFile& addWav = *(additionalInputs[fileIndex]);

    const std::vector<int16_t>& mainSamples = mainStream;
    const std::vector<int16_t>& addSamples = addWav.getSamples();


    std::vector<int16_t> outSamples = mainSamples;
    int insertIndex = insert * sampleRate;
    int minSize = (mainStream.size() < addSamples.size()) ? mainStream.size() : addSamples.size();
    for (int i = 0; i < minSize; ++i) {
        int outPos = insertIndex + i;
        if (outPos >= outSamples.size()) {
            break;
        }
        int32_t mixed = (int32_t)outSamples[outPos] + (int32_t)addSamples[i];
        mixed /= 2;
        outSamples[outPos] = (int16_t)mixed;
    }

    return outSamples;
}

std::string MixConverter::getDescription() const {
    return "mix $<n> <insert_sec>\n"
           "Mixes the main audio with the additional input $n starting at insert_sec.\n";
}

EchoConverter::EchoConverter(int delaySec, float attenuation)
        : delaySec(delaySec), attenuation(attenuation) {}

std::vector<int16_t> EchoConverter::convert(const std::vector<int16_t>& mainStream, const std::vector<WavFile*>& additionalInputs) const {
    const std::vector<int16_t>& inSamples = mainStream;
    std::vector<int16_t> outSamples = inSamples;

    int16_t delaySamples = (int16_t)(delaySec * sampleRate);
    for (int i = delaySamples; i < outSamples.size(); i++) {
        int16_t val = outSamples[i] + (int16_t)(outSamples[i - delaySamples] * attenuation);
        if (val > std::numeric_limits<int16_t>::max())
            val = std::numeric_limits<int16_t>::max();
        if (val < std::numeric_limits<int16_t>::min())
            val = std::numeric_limits<int16_t>::min();
        outSamples[i] = (int16_t)val;
    }

    return outSamples;
}

std::string EchoConverter::getDescription() const {
    return "echo <delay_sec> <attenuation>\n"
           "Adds an echo effect with given delay and attenuation.\n";
}