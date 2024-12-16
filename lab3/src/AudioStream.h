#ifndef LAB3_AUDIOSTREAH
#define LAB3_AUDIOSTREAH

#include <vector>
#include <cstdint>

class AudioStream {
public:
    virtual ~AudioStream() {}
    virtual const std::vector<int16_t>& getSamples() const = 0;
    virtual int getSampleRate() const = 0;
};

class WavFile;

class MemoryAudioStream : public AudioStream {
private:
    const std::vector<int16_t>& samples;
    int sampleRate;
public:
    MemoryAudioStream(const WavFile &wav);
    MemoryAudioStream(const std::vector<int16_t>& samples, int rate);
    virtual ~MemoryAudioStream() {}
    const std::vector<int16_t>& getSamples() const override;
    int getSampleRate() const override;
};

class OwnedMemoryAudioStream : public AudioStream {
private:
    std::vector<int16_t> samplesOwned;
    int sampleRate;
public:
    OwnedMemoryAudioStream(std::vector<int16_t> samples, int rate);
    virtual ~OwnedMemoryAudioStream() {}
    const std::vector<int16_t>& getSamples() const override;
    int getSampleRate() const override;

};

#endif //LAB3_AUDIOSTREAH
