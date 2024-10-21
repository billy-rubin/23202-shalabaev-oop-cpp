set(SOURCES
        FileReader.cpp
        FileWriter.cpp
        TransferToTable.cpp
        Statistics.cpp
        Parser.cpp
)

set(HEADERS
        FileReader.h
        FileWriter.h
        TransferToTable.h
        Statistics.h
        Parser.h
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})