#include "audiostream.h"
#include "WavHeader.h"

MemoryAudioStream::MemoryAudioStream(const WavFile &wav)
        : samples(wav.getSamples()), sampleRate(wav.getSampleRate()) {}

MemoryAudioStream::MemoryAudioStream(const std::vector<int16_t>& samples, uint32_t rate)
        : samples(samples), sampleRate(rate) {}

const std::vector<int16_t>& MemoryAudioStream::getSamples() const {
    return samples;
}

int MemoryAudioStream::getSampleRate() const {
    return sampleRate;
}

OwnedMemoryAudioStream::OwnedMemoryAudioStream(std::vector<int16_t> samples, uint32_t rate)
        : samplesOwned(std::move(samples)), sampleRate(rate) {}

const std::vector<int16_t>& OwnedMemoryAudioStream::getSamples() const {
    return samplesOwned;
}

int OwnedMemoryAudioStream::getSampleRate() const {
    return sampleRate;
}
