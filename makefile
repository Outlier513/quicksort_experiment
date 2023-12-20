cpp_srcs := $(wildcard src/*.cpp)
so_libs := $(patsubst src/%.cpp,libs/%.so,$(cpp_srcs))

compile : $(so_libs)

libs/%.so : src/%.cpp
	@if not exist libs (md libs)
	@g++ $^ -fPIC -shared -o $@ 

clean :
	@if exist libs rmdir libs  /s /q

debug :
	@echo $(cpp_srcs)
	@echo $(so_libs)

.PHONY :
	debug, clean, compile