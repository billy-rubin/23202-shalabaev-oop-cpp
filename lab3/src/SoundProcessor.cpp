#include "SoundProcessor.h"
#include "ConfigParser.h"
#include "AudioStream.h"
#include "ExceptionsHandler.h"
#include "Converter.h"
#include "WavHeader.h"
#include <iostream>
SoundProcessor::SoundProcessor(const std::string& configFile, const std::string& outputFile, const std::vector<std::string>& inputFiles)
        : configFile(configFile), outputFile(outputFile), inputFiles(inputFiles), currentStream(nullptr) {
}

SoundProcessor::~SoundProcessor() {
    for (auto &kv : inputWavs) {
        delete kv.second;
    }
    inputWavs.clear();

    if (currentStream) {
        delete currentStream;
        currentStream = nullptr;
    }
}

void SoundProcessor::load() {
    if (inputFiles.empty()) {
        throw InvalidArgumentsException("No input files.");
    }
    for (int i = 0; i < inputFiles.size(); ++i) {
        WavFile* w = new WavFile();
        w->load(inputFiles[i]);
        inputWavs[i+1] = w;
    }
}

int SoundProcessor::run() {
    try {
        load();
        ConfigParser parser(configFile, factory);
        std::vector<Converter*> converters = parser.parse();

        currentStream = new MemoryAudioStream(*inputWavs[1]);

        std::map<int, WavFile*> additionalInputs = inputWavs;

        for (Converter* conv : converters) {
            AudioStream* newStream = conv->convert(*currentStream, additionalInputs);
            delete currentStream;
            currentStream = newStream;
        }

        for (Converter* c : converters) {
            delete c;
        }

        WavFile output;
        const std::vector<int16_t> outSamples = currentStream->getSamples();
        output.getSamples() = outSamples;
        output.save(outputFile);

        return 0;
    } catch (SoundProcessorException &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return (int)ex.getCode();
    } catch (std::exception &ex) {
        std::cerr << "Unknown error: " << ex.what() << "\n";
        return (int)ErrorCode::UNKNOWN_ERROR;
    }
}