# some make macros that just call cmake commands and stuff

all: build set_debug set_release
.PHONY: build build_release

default:
	@ echo "nothing to do"

# make commands 
debug:
	@ make -s set_debug
	@ make -s build

release:
	@ make - set_release
	@ make - build_release

test_valgrind:
	@ make -s set_debug
	@ make -s build
	@ make -s run_test_valgrind

# auxiliary commands
set_debug:
	@ cmake -DCMAKE_BUILD_TYPE=Debug build

set_release:
	@ cmake -DCMAKE_BUILD_TYPE=Release build_release

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
