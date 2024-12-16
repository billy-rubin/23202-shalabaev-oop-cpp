#ifndef LAB3_SOUNDPROCESSOR_H
#define LAB3_SOUNDPROCESSOR_H
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "converterfactory.h"
#include "WavHeader.h"
#include "AudioStream.h"

class SoundProcessor {
public:
    SoundProcessor(const std::string& configFile,
                      const std::string& outputFile,
                      const std::vector<std::string>& inputFiles);
    ~SoundProcessor();
    int run();

private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    ConverterFactory factory;

    std::map<int, WavFile*> inputWavs;
    AudioStream* currentStream;

    void load();
};
#endif //LAB3_SOUNDPROCESSOR_H
