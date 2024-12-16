set(SOURCES
        AudioStream.cpp
        ConfigParser.cpp
        Converter.cpp
        ConverterFactory.cpp
        ExceptionsHandler.cpp
        SoundProcessor.cpp
        WavHeader.cpp
        CmdParser.cpp
)

set(HEADERS
        AudioStream.h
        ConfigParser.h
        Converter.h
        ConverterFactory.h
        ExceptionsHandler.h
        SoundProcessor.h
        WavHeader.h
        CmdParser.h
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})