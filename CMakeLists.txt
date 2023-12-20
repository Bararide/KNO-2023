cmake_minimum_required(VERSION 3.12)
project(genome)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

set(SOURCES
    Error_handler/Error.cpp
    Lexical_analysis/Lexical_analysis.cpp
    Lexical_analysis/IT.cpp
    Lexical_analysis/LT.cpp
    Lexical_analysis/RPN.cpp  
    Lexical_analysis/Block_analysis.cpp 

    Broadcaster/translator.cpp  

    MFST/GRB.cpp
    MFST/MFST.cpp

    Main/main.cpp
    Main/In.cpp
    Main/Log.cpp
    Main/Out.cpp
    Main/Parm.cpp
)

set(HEADERS
    Error_handler/Error.h
    Lexical_analysis/Lexical_analysis.h
    Lexical_analysis/IT.h
    Lexical_analysis/LT.h
    Lexical_analysis/Graph.h
    Lexical_analysis/RPN.h

    Broadcaster/translator.h

    MFST/GRB.h
    MFST/MFST.h
    MFST/Rules.h
    
    Main/In.h
    Main/Log.h
    Main/Out.h
    Main/Parm.h

    Meta/Meta.h
    Meta/Meta_container.h
    Meta/Meta_fst.h
    Meta/Meta_helper.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})