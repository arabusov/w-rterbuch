root_include_dir    := include
root_source_dir    := src
source_subdirs    := . 
compile_flags      := -Wall -Wextra -pipe -std=c++11
link_flags            := -s -pipe
libraries               := 
         
relative_include_dirs	:= $(addprefix ../../, $(root_include_dir))
relative_source_dirs	:= $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
objects_dirs					:= $(addprefix $(root_source_dir)/, $(source_subdirs))
objects               := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.c*, $(relative_source_dirs))))
objects               := $(objects:.cpp=.o)
objects               := $(objects:.c=.o)
         
all : $(program_name)
         
$(program_name) : obj_dirs $(objects)
	g++ -o $@ $(objects) $(link_flags) $(libraries)
         
obj_dirs :
	mkdir -p $(objects_dirs)
         
VPATH := ../../
         
%.o : %.cpp
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
         
%.o : %.c
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
         
.PHONY : clean
         
clean :
	rm -rf bin obj

prepare:
	mkdir -p bin
	mkdir -p obj
	mkdir -p obj/Debug
	mkdir -p obj/Release

release: prepare
	make --directory=./obj/Release --makefile=../../Makefile build_flags="-O2 -fomit-frame-pointer" program_name=../../bin/dict

debug: prepare
	make --directory=./obj/Debug --makefile=../../Makefile build_flags="-O0 -g3 -D_DEBUG" program_name=../../bin/dict_debug
         
include $(wildcard $(addsuffix /*.d, $(objects_dirs)))

