@set b_CC=%CC%
@set b_CXX=%CXX%
@set target=ninja

@set CC=clang-cl
@set CXX=clang-cl
@md %target%
@cd %target%
@cmake -G "Ninja" -DUNITY_BUILD=OFF ..
@cd ..

@set CC=%b_CC%
@set CXX=%b_CXX%
@set target=

