cmake_minimum_required(VERSION 2.8)
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
    SET(NAME ${NAME}.out)
    add_executable(${NAME} ${exec} ${LIBS})
endforeach ()