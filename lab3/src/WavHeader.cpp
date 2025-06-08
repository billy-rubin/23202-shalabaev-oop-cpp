#include "WavHeader.h"

WavFile::WavFile() {
    std::memcpy(chunkID, "RIFF", 4);
    std::memcpy(format, "WAVE", 4);
    std::memcpy(subchunk1ID, "fmt ", 4);
    std::memcpy(subchunk2ID, "data",4);
    subchunk1Size = 16;
    audioFormat = 1;
    numChannels = 1;
    sampleRate = 44100;
    bitsPerSample = 16;
    byteRate = sampleRate*numChannels*bitsPerSample/8;
    blockAlign = numChannels*bitsPerSample/8;
    subchunk2Size = 0;
    chunkSize = 36 + subchunk2Size;
}

void WavFile::load(const std::string& filename) {
    std::ifstream inputFile(filename, std::ios::binary);

    inputFile.read(chunkID, 4); // RIFF
    if(!inputFile)
        throw FileIOException("Cannot read WAV header: " + filename);
    inputFile.read(reinterpret_cast<char*>(&chunkSize), 4); //размер оставшейся цепочки
    inputFile.read(format, 4); // WAVE
    inputFile.read(subchunk1ID, 4); // fmt
    inputFile.read(reinterpret_cast<char*>(&subchunk1Size), 4); //PCM format
    inputFile.read(reinterpret_cast<char*>(&audioFormat), 2); // формат сжатия
    inputFile.read(reinterpret_cast<char*>(&numChannels), 2); // Кол-во каналов
    inputFile.read(reinterpret_cast<char*>(&sampleRate), 4); // Частота дискрет.
    inputFile.read(reinterpret_cast<char*>(&byteRate), 4); // bytePerSecond
    inputFile.read(reinterpret_cast<char*>(&blockAlign), 2); // кол-во байт для 1 сэмпла
    inputFile.read(reinterpret_cast<char*>(&bitsPerSample), 2); // bitsPerSample

    bool dataFound = false;
    while (!dataFound) {
        char chunk[4]; //List и мусор
        if (!inputFile.read(chunk, 4)) {
            throw UnsupportedFormatException("No data chunk found inputFile WAV file: " + filename);
        }
        int subChunkSizeTemp = 0;
        if (!inputFile.read(reinterpret_cast<char *>(&subChunkSizeTemp), 4)) {
            throw FileIOException("Cannot read subchunk size inputFile file: " + filename);
        }

        if (std::strncmp(chunk, "data", 4) == 0) {
            std::memcpy(subchunk2ID, chunk, 4);
            subchunk2Size = subChunkSizeTemp;
            dataFound = true;
        } else {
            inputFile.ignore(subChunkSizeTemp);
        }
    }

    if (std::strncmp(chunkID, "RIFF", 4) != 0 ||
        std::strncmp(format, "WAVE", 4) != 0 ||
        std::strncmp(subchunk1ID, "fmt ", 4) != 0 ||
        std::strncmp(subchunk2ID, "data",4) != 0 ||
        audioFormat != 1 ||
        numChannels != 1 ||
        sampleRate != 44100 ||
        bitsPerSample != 16) {
        throw UnsupportedFormatException("Unsupported WAV format inputFile: " + filename);
    }

    int dataSize = subchunk2Size;
    int numSamples = dataSize / (bitsPerSample/8) / numChannels;
    samples.resize(numSamples);
    if(!inputFile.read(reinterpret_cast<char*>(samples.data()), dataSize)) {
        throw FileIOException("Cannot read samples from: " + filename);
    }

}

void WavFile::save(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if(!out) {
        throw FileIOException("Cannot open output file: " + filename);
    }

    byteRate = sampleRate * numChannels * (bitsPerSample/8);
    blockAlign = numChannels * (bitsPerSample/8);
    subchunk2Size = (samples.size() * numChannels * (bitsPerSample/8));
    chunkSize = 36 + subchunk2Size;

    out.write(chunkID,4);
    out.write(reinterpret_cast<char*>(&chunkSize),4);
    out.write(format,4);
    out.write(subchunk1ID,4);
    out.write(reinterpret_cast<char*>(&subchunk1Size),4);
    out.write(reinterpret_cast<char*>(&audioFormat),2);
    out.write(reinterpret_cast<char*>(&numChannels),2);
    out.write(reinterpret_cast<char*>(&sampleRate),4);
    out.write(reinterpret_cast<char*>(&byteRate),4);
    out.write(reinterpret_cast<char*>(&blockAlign),2);
    out.write(reinterpret_cast<char*>(&bitsPerSample),2);
    out.write(subchunk2ID,4);
    out.write(reinterpret_cast<char*>(&subchunk2Size),4);
    out.write(reinterpret_cast<char*>(samples.data()), subchunk2Size);
    if(!out) {
        throw FileIOException("Cannot write WAV data to: " + filename);
    }
}

std::vector<int16_t>& WavFile::getSamples() {
    return samples;
}

const std::vector<int16_t>& WavFile::getSamples() const {
    return samples;
}
