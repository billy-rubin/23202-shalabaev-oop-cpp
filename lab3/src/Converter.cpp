#include "Converter.h"


MuteConverter::MuteConverter(int startSec, int endSec)
        : start(startSec), end(endSec) {}

AudioStream* MuteConverter::convert(const AudioStream& mainStream,
                                    const std::map<int, WavFile*>&) const {
    int rate = mainStream.getSampleRate();
    std::vector<int16_t> outSamples = mainStream.getSamples();

    int startIndex = start * rate;
    int endIndex   = end * rate;
    if (endIndex > outSamples.size()) {
        endIndex = outSamples.size();
    }
    if (startIndex < endIndex && startIndex < outSamples.size()) {
        std::fill(outSamples.begin() + startIndex,outSamples.begin() + endIndex,0);
    }

    return new OwnedMemoryAudioStream(outSamples, rate);
}

MixConverter::MixConverter(int fileIndex, int insertSec)
        : fileIndex(fileIndex), insert(insertSec) {}

AudioStream* MixConverter::convert(const AudioStream& mainStream,
                                   const std::map<int, WavFile*>& additionalInputs) const {
    if (additionalInputs.count(fileIndex) == 0) {
        throw ConversionException("Mix: additional input not found for index " + std::to_string(fileIndex));
    }
    const WavFile& addWav = *(additionalInputs.find(fileIndex)->second);

    const std::vector<int16_t>& mainSamples = mainStream.getSamples();
    const std::vector<int16_t>& addSamples = addWav.getSamples();
    int rate = mainStream.getSampleRate();

    std::vector<int16_t> outSamples = mainSamples;
    int insertIndex = insert * rate;

    for (int i = 0; i < addSamples.size(); ++i) {
        int outPos = insertIndex + i;
        if (outPos >= outSamples.size()) {
            break;
        }
        int32_t mixed = (int32_t)outSamples[outPos] + (int32_t)addSamples[i];
        mixed /= 2;
        if (mixed > std::numeric_limits<int16_t>::max()) mixed = std::numeric_limits<int16_t>::max();
        if (mixed < std::numeric_limits<int16_t>::min()) mixed = std::numeric_limits<int16_t>::min();
        outSamples[outPos] = (int16_t)mixed;
    }

    return new OwnedMemoryAudioStream(outSamples, rate);
}

EchoConverter::EchoConverter(int delaySec, float attenuation)
        : delaySec(delaySec), attenuation(attenuation) {}

AudioStream* EchoConverter::convert(const AudioStream& mainStream, const std::map<int, WavFile*>&) const {
    const std::vector<int16_t>& inSamples = mainStream.getSamples();
    uint32_t rate = mainStream.getSampleRate();
    std::vector<int16_t> outSamples = inSamples;

    int delaySamples = (int)(delaySec * rate);
    for (int i = delaySamples; i < outSamples.size(); i++) {
        int32_t val = (int32_t)outSamples[i] + (int32_t)(outSamples[i - delaySamples] * attenuation);
        if (val > std::numeric_limits<int16_t>::max()) val = std::numeric_limits<int16_t>::max();
        if (val < std::numeric_limits<int16_t>::min()) val = std::numeric_limits<int16_t>::min();
        outSamples[i] = (int16_t)val;
    }

    return new OwnedMemoryAudioStream(outSamples, rate);
}