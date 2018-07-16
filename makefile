#
# Copyright (c) 2017 Milos Toisc. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
#

GENIE=../build/tools/$(OS)/genie

all:
	$(GENIE) vs2015
	$(GENIE) vs2017
	$(GENIE) --gcc=android-arm gmake
	$(GENIE) --gcc=android-mips gmake
	$(GENIE) --gcc=android-x86 gmake
	$(GENIE) --gcc=mingw-gcc gmake
	$(GENIE) --gcc=linux-gcc gmake
	$(GENIE) --gcc=osx gmake
	$(GENIE) --gcc=ios-arm gmake
	$(GENIE) --gcc=ios-simulator gmake
	$(GENIE) --gcc=ios-simulator64 gmake
	$(GENIE) xcode4 

gmake-linux:
	$(GENIE) --file=genie/genie.lua --gcc=linux-gcc gmake
#linux-debug32: gmake-linux
#	make -R -C ../.build/linux/gcc/MTuner/projects config=debug32
#linux-release32: gmake-linux
#	make -R -C ../.build/linux/gcc/MTuner/projects config=release32
linux-debug64: gmake-linux
	make -R -C ../.build/linux/gcc/MTuner/projects config=debug64
linux-release64: gmake-linux
	make -R -C ../.build/linux/gcc/MTuner/projects config=release64
linux: linux-debug64 linux-release64

gmake-mingw-gcc:
	$(GENIE) --file=genie/genie.lua --gcc=mingw-gcc gmake
#mingw-gcc-debug32: gmake-mingw-gcc
#	make -R -C ../.build/windows/mingw-gcc/MTuner/projects config=debug32
#mingw-gcc-release32: gmake-mingw-gcc
#	make -R -C ../.build/windows/mingw-gcc/MTuner/projects config=release32
mingw-gcc-debug64: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/MTuner/projects config=debug64
mingw-gcc-release64: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/MTuner/projects config=release64
mingw-gcc: mingw-gcc-debug64 mingw-gcc-release64

gmake-mingw-clang:
	$(GENIE) --file=genie/genie.lua --clang=mingw-clang gmake
#mingw-clang-debug32: gmake-mingw-clang
#	make -R -C ../.build/windows/mingw-clang/MTuner/projects config=debug32
#mingw-clang-release32: gmake-mingw-clang
#	make -R -C ../.build/windows/mingw-clang/MTuner/projects config=release32
mingw-clang-debug64: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/MTuner/projects config=debug64
mingw-clang-release64: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/MTuner/projects config=release64
mingw-clang: mingw-clang-debug64 mingw-clang-release64

vs2015:
	$(GENIE) --file=genie/genie.lua vs2015

vs2017:
	$(GENIE) --file=genie/genie.lua vs2017

../.build/osx/gcc/MTuner/projects:
	$(GENIE) --file=genie/genie.lua --gcc=osx gmake
osx-debug64: ../.build/osx/gcc/MTuner/projects
	make -C ../.build/osx/gcc/MTuner/projects config=debug64
osx-release64: ../.build/osx/gcc/MTuner/projects
	make -C ../.build/osx/gcc/MTuner/projects config=release64
osx: osx-debug64 osx-release64

clean:
	@echo Cleaning...
	-@rm -rf ../.build

###

SILENT ?= @

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux GNU Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
endif
else
OS=windows
endif 

