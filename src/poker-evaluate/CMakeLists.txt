SET(sources
    poker-evaluate.cc
    hand-eval.cc
)

IF(UNITY_BUILD)
    enable_unity_build(libpoker-evaluate sources)
ENDIF()

ADD_LIBRARY(libpoker-evaluate STATIC ${sources})

