SET(sources
    poker-evaluate.cc
    hand-eval.cc
)

IF(UNITY_BUILD)
    enable_unity_build(libpoker-evaluate sources)
ENDIF()

ADD_LIBRARY(libpoker-evaluate ${sources})

#ADD_EXECUTABLE(libpoker-evaluate ${sources})
#
#SET_TARGET_PROPERTIES(libpoker-evaluate
#    PROPERTIES ENABLE_EXPORTS ON
#)

