SET(sources
    hand-eval.cc
    hand-parse.cc
    hand-value.cc
    bits.cc
)

IF(UNITY_BUILD)
    enable_unity_build(test-poker-evaluate sources)
ENDIF()

ADD_EXECUTABLE(test-poker-evaluate ${sources})
TARGET_LINK_LIBRARIES(test-poker-evaluate libtest-main libpoker-evaluate)

ADD_CUSTOM_TARGET(run-tests
    COMMAND test-poker-evaluate
    DEPENDS test-poker-evaluate
    VERBATIM
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

