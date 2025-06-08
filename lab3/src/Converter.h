#ifndef LAB3_CONVERTER_H
#define LAB3_CONVERTER_H
#include "WavHeader.h"
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <string>

class Converter {
protected:
    const int sampleRate = 44100;
public:
    Converter() = default;
    virtual ~Converter() {}
    virtual std::vector<int16_t> convert(const std::vector<int16_t>& mainStream, const std::vector<WavFile*>& additionalInputs) const = 0;
    virtual std::string getDescription() const = 0;
};

class MuteConverter : public Converter {
private:
    int start;
    int end;
public:
    MuteConverter() : Converter() {}
    MuteConverter(int startSec, int endSec);
    virtual ~MuteConverter() {}
    std::vector<int16_t> convert(const std::vector<int16_t>& mainStream, const std::vector<WavFile*>& additionalInputs) const override;
    std::string getDescription() const override;

};

class MixConverter : public Converter {
private:
    int fileIndex;
    int insert;
public:
    MixConverter() : Converter() {}
    MixConverter(int fileIndex, int insertSec);
    virtual ~MixConverter() {}
    std::vector<int16_t> convert(const std::vector<int16_t>& mainStream, const std::vector<WavFile*>& additionalInputs) const override;
    std::string getDescription() const override;
};

class EchoConverter : public Converter {
private:
    int delaySec;
    float attenuation;
public:
    EchoConverter() : Converter() {}
    EchoConverter(int delaySec, float attenuation);
    virtual ~EchoConverter() {}
    std::vector<int16_t> convert(const std::vector<int16_t>& mainStream, const std::vector<WavFile*>& additionalInputs) const override;
    std::string getDescription() const override;
};

#endif //LAB3_CONVERTER_H
