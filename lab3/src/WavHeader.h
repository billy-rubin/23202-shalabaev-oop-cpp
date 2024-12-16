#ifndef WAVFILE_H
#define WAVFILE_H

#include "ExceptionsHandler.h"
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>

class WavFile {
public:
    WavFile();
    void load(const std::string& filename);
    void save(const std::string& filename);

    std::vector<int16_t>& getSamples();
    const std::vector<int16_t>& getSamples() const;

    int getSampleRate() const;

protected:
    char chunkID[4];
    int chunkSize;
    char format[4];
    char subchunk1ID[4];
    int subchunk1Size;
    int audioFormat;
    int numChannels;
    int sampleRate;
    int byteRate;
    int blockAlign;
    int bitsPerSample;
    char subchunk2ID[4];
    int subchunk2Size;

private:
    std::vector<int16_t> samples;
};

#endif