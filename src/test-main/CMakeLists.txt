SET(sources
    test-main.cc
)

ADD_LIBRARY(libtest-main ${sources})
TARGET_INCLUDE_DIRECTORIES(libtest-main PUBLIC ${CMAKE_SOURCE_DIR}/src/third-party)
