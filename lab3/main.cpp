#include "soundprocessor.h"
#include "CmdParser.h"
#include "converterfactory.h"

int main(int argc, char** argv) {
    CmdParser cmdParser(argc, argv);

    if (!cmdParser.parseArguments()) {
        return (int)ErrorCode::INVALID_ARGUMENTS;
    }

    if (cmdParser.showHelp()) {
        cmdParser.printHelp();
        return 0;
    }

    SoundProcessor soundProcessor(cmdParser.getConfigFile(),cmdParser.getOutputFile(), cmdParser.getInputFiles());
    return soundProcessor.run();
}
