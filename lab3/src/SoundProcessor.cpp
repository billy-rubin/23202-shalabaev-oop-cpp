#include "SoundProcessor.h"

SoundProcessor::SoundProcessor(const std::string& configFile, const std::string& outputFile, const std::vector<std::string>& inputFiles, std::vector<int16_t> audioStream)
        : configFile(configFile), outputFile(outputFile), inputFiles(inputFiles), currentStream(audioStream) {
}

SoundProcessor::~SoundProcessor() {
    if (!currentStream.empty()) {
        currentStream.clear();
    }
}

void SoundProcessor::load() {
    if (inputFiles.empty()) {
        throw InvalidArgumentsException("No input files.");
    }
    for (int i = 0; i < inputFiles.size(); ++i) {
        WavFile* w = new WavFile();
        w->load(inputFiles[i]);
        inputWaves.push_back(w);
    }
}

int SoundProcessor::run() {
    try {
        load();

        ConfigParser parser(configFile);
        std::vector<Converter*> converters = parser.parse();

        currentStream = inputWaves[0]->getSamples();

        std::vector<WavFile*> addInputs = inputWaves;
        for (Converter* conv : converters) {
            std::vector<int16_t> newStream = conv->convert(currentStream, addInputs);
            currentStream.clear();
            currentStream = newStream;
        }

        for (Converter* c : converters) {
            delete c;
        }

        WavFile output;
        const std::vector<int16_t> outSamples = currentStream;
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