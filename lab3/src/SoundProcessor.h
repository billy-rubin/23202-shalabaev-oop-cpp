#ifndef LAB3_SOUNDPROCESSOR_H
#define LAB3_SOUNDPROCESSOR_H
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "ConverterFactory.h"
#include "WavHeader.h"
#include "ConfigParser.h"
#include "ExceptionsHandler.h"
#include <iostream>
#include "regex"
class SoundProcessor {
public:
    SoundProcessor(const std::string& configFile,
                      const std::string& outputFile,
                      const std::vector<std::string>& inputFiles,
                      std::vector<int16_t> audioStream);
    ~SoundProcessor();
    int run();

private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    std::vector<WavFile*> inputWaves;
    std::vector<int16_t>& currentStream;

    void load();
};
#endif //LAB3_SOUNDPROCESSOR_H
