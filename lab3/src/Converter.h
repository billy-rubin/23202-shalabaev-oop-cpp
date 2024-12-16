#ifndef LAB3_CONVERTER_H
#define LAB3_CONVERTER_H
#include "WavHeader.h"
#include "AudioStream.h"
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <string>

class Converter {
public:
    virtual ~Converter() {}
    // Return a newly allocated AudioStream. Caller must delete it.
    virtual AudioStream* convert(const AudioStream& mainStream,
                                 const std::map<int, WavFile*>& additionalInputs) const = 0;
};

class MuteConverter : public Converter {
private:
    int start;
    int end;
public:
    MuteConverter(int startSec, int endSec);
    virtual ~MuteConverter() {}
    AudioStream* convert(const AudioStream& mainStream, const std::map<int, WavFile*>& additionalInputs) const override;
};

class MixConverter : public Converter {
private:
    int fileIndex;
    int insert;
public:
    MixConverter(int fileIndex, int insertSec);
    virtual ~MixConverter() {}
    AudioStream* convert(const AudioStream& mainStream, const std::map<int, WavFile*>& additionalInputs) const override;
};

class EchoConverter : public Converter {
private:
    int delaySec;
    float attenuation;
public:
    EchoConverter(int delaySec, float attenuation);
    virtual ~EchoConverter() {}
    AudioStream* convert(const AudioStream& mainStream, const std::map<int, WavFile*>& additionalInputs) const override;
};

#endif //LAB3_CONVERTER_H
