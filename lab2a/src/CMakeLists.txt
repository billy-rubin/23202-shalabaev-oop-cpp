set(SOURCES
        FileManager.cpp
        Game.cpp
        Rules.cpp
        Universe.cpp
        Grid.cpp
        DumpCommandExecutor.cpp
        TickCommandExecutor.cpp
        ExitCommandExecutor.cpp
        HelpCommandExecutor.cpp
        CommandHandler.cpp
)

set(HEADERS
        FileManager.h
        Game.h
        Rules.h
        Universe.h
        Grid.h
        CommandHandler.h
        CommandExecutor.h
        DumpCommandExecutor.h
        TickCommandExecutor.h
        HelpCommandExecutor.h
        ExitCommandExecutor.h
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})