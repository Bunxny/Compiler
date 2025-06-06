cmake_minimum_required(VERSION 3.1)
project(tiger)

set(CMAKE_CXX_STANDARD 20)
#  :-(   this seems not to catch "overrode a function not marked as virtual", though C-Lion warns of it >:-(
#  :-(      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
#        (note that C-Lion does auto-suggest on the variable _usage_, if I want to play with it)


# Bison/Flex stuff documented here: https://cmake.org/cmake/help/v2.8.8/cmake.html#module:FindFLEX
find_package(BISON)
find_package(FLEX)

BISON_TARGET(TigerParser tiger-grammar.yy ${CMAKE_CURRENT_BINARY_DIR}/tiger-grammar.tab.cpp)
FLEX_TARGET(TigerScanner tiger-lex.ll  ${CMAKE_CURRENT_BINARY_DIR}/tiger-lex.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(TigerScanner TigerParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
# Thanks, cmake.org., for the above and ...OUTPUTS dependencies on the list below
#   but, note I added CMAKE_CURRENT_SOURCE_DIR to the above
   
add_executable(tiger
        ${BISON_TigerParser_OUTPUTS}
        ${FLEX_TigerScanner_OUTPUTS}
        AST.cpp
        AST-print-attributes.cpp
        AST-print.cpp
        depth.cpp
        errormsg.cpp
        height.cpp
        HERA_code.cpp
        layout_frames.cpp
        lazy.cpp
        parent.cpp
        result_reg.cpp
        static_checks.cpp
        ST.cpp
        tiger.cpp
        tigerParseDriver.cpp
        typecheck.cpp
        types.cpp
        util.cpp
)

include_directories(/home/courses/include ../HaverfordCS/include)
