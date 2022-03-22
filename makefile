# Still uses cmake. This makefile just makes writing common
# commands more convenient

all: build set_windows set_debug set_linux set_release
.PHONY: build build_release

default:
	@ echo "nothing todo"

debug:
	@ make -s set_debug 
	@ make -s build

release:
	@ make -s set_release
	@ make -s build_release

test:
	@ make -s build
	@	make -s run_test 

test_valgrind:
	@	make -s set_debug
	@ make -s build
	@	make -s run_test_valgrind

# you should set it to release or debug before running this
opengltest:
	@ make -s build 
	@./build/sandbox/opengltest
	
# silent stuff
set_debug:
	@ cmake -DCMAKE_BUILD_TYPE=Debug build

set_release:
	@ cmake -DCMAKE_BUILD_TYPE=Release build_release

set_linux:
	@ cmake -DBUILD_LINUX=ON build
	@ cmake -DBUILD_WINDOWS=OFF build

set_windows:
	@ cmake -DBUILD_LINUX=OFF build
	@ cmake -DBUILD_WINDOWS=ON build

build:
	@ cmake --build build
	@ echo built

build_release:
	@ cmake --build build_release
	@ echo built release

run_test:
	@ ./build/tests/tests

run_test_valgrind:
	@ valgrind ./build/tests/tests

generate_docs:
	@ doxygen Doxyfile
