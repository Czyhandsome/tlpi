cmake_minimum_required(VERSION 3.15)
project(linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

file(GLOB LIBS lib/*.c)

file(GLOB APPS "src/*/*.c")

set(EXECUTABLE_APPS ${APPS})

foreach (exec ${EXECUTABLE_APPS})
    STRING(REGEX MATCH
            "[^ /]+\\.c"
            NAME ${exec})
    add_executable(${NAME} ${exec} ${LIBS})
endforeach ()