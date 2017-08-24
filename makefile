#
# Copyright (c) 2017 Milos Toisc. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
#

GENIE=../build/tools/$(OS)/genie

all:
	$(GENIE) vs2012
	$(GENIE) vs2013
	$(GENIE) vs2015
	$(GENIE) vs2017
	$(GENIE) --gcc=mingw-clang gmake
	$(GENIE) --gcc=mingw-gcc gmake
	$(GENIE) --gcc=linux-gcc gmake

gmake-linux:
	$(GENIE) --file=genie/genie.lua --gcc=linux-gcc gmake
linux-debug32: gmake-linux
	make -R -C ../.build/linux/gcc/projects/MTuner config=debug32
linux-release32: gmake-linux
	make -R -C ../.build/linux/gcc/projects/MTuner config=release32
linux-debug64: gmake-linux
	make -R -C ../.build/linux/gcc/projects/MTuner config=debug64
linux-release64: gmake-linux
	make -R -C ../.build/linux/gcc/projects/MTuner config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64

gmake-mingw-gcc:
	$(GENIE) --file=genie/genie.lua --gcc=mingw-gcc gmake
mingw-gcc-debug32: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/projects/MTuner config=debug32
mingw-gcc-release32: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/projects/MTuner config=release32
mingw-gcc-debug64: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/projects/MTuner config=debug64
mingw-gcc-release64: gmake-mingw-gcc
	make -R -C ../.build/windows/mingw-gcc/projects/MTuner config=release64
mingw-gcc: mingw-gcc-debug32 mingw-gcc-release32 mingw-gcc-debug64 mingw-gcc-release64

gmake-mingw-clang:
	$(GENIE) --file=genie/genie.lua --clang=mingw-clang gmake
mingw-clang-debug32: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/projects/MTuner config=debug32
mingw-clang-release32: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/projects/MTuner config=release32
mingw-clang-debug64: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/projects/MTuner config=debug64
mingw-clang-release64: gmake-mingw-clang
	make -R -C ../.build/windows/mingw-clang/projects/MTuner config=release64
mingw-clang: mingw-clang-debug32 mingw-clang-release32 mingw-clang-debug64 mingw-clang-release64

vs2012:
	$(GENIE) --file=genie/genie.lua vs2012

vs2013:
	$(GENIE) --file=genie/genie.lua vs2013

vs2015:
	$(GENIE) --file=genie/genie.lua vs2015

vs2017:
	$(GENIE) --file=genie/genie.lua vs2017

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

