#include "soundprocessor.h"
#include "CmdParser.h"
#include "ConverterFactory.h"

int main(int argc, char** argv) {
    CmdParser cmdParser(argc, argv);

    if (!cmdParser.parseArguments()) {
        return (int)ErrorCode::INVALID_ARGUMENTS;
    }
    if (cmdParser.showHelp()) {
        cmdParser.printHelp();
        std::vector<Converter *> converters = {
                new MuteConverter(),
                new MixConverter(),
                new EchoConverter()
        };
        for (const auto &converter: converters) {
            std::cout << converter->getDescription();
        }
        return 0;
    }

    std::vector<int16_t> audioStream;
    SoundProcessor soundProcessor(cmdParser.getConfigFile(),cmdParser.getOutputFile(), cmdParser.getInputFiles(), audioStream);
    return soundProcessor.run();
}
