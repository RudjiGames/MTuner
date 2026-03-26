#
# Copyright 2025-2026 Milos Tosic. All rights reserved.
# License: https://github.com/RudjiGames/rg_core/blob/master/LICENSE
#

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
endif

help:
	@echo Available targets:
	@grep -E "^[a-zA-Z0-9_-]+:.*?## .*$$" $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
else
OS=windows

help:
	@echo Available targets:
	@for /F "tokens=1,2 delims=#" %%a in ('findstr /R /C:"^[a-zA-Z0-9_-]*:.*## " $(MAKEFILE_LIST)') do @echo   [36m%%a[0m %%b
endif

GetParentDir  = $(dir ${1:/=})

RG_ZIDAR_DIR?=
# If RG_ZIDAR_DIR does not exist, search parent directories for 'zidar'
# 7 levels up should be enough for most cases, but can be increased if needed.
ifeq ($(wildcard $(RG_ZIDAR_DIR)),)
  _d0 := $(CURDIR)/
  _d1 := $(call GetParentDir, $(_d0))
  _d2 := $(call GetParentDir, $(_d1))
  _d3 := $(call GetParentDir, $(_d2))
  _d4 := $(call GetParentDir, $(_d3))
  _d5 := $(call GetParentDir, $(_d4))
  _d6 := $(call GetParentDir, $(_d5))
  _d7 := $(call GetParentDir, $(_d6))
  RG_ZIDAR_DIR := $(firstword $(foreach d,$(_d0) $(_d1) $(_d2) $(_d3) $(_d4) $(_d5) $(_d6) $(_d7),$(wildcard $(d)zidar)))
  ifeq ($(RG_ZIDAR_DIR),)
    $(error RG_ZIDAR_DIR not found in any parent directory)
  endif
endif

GENIE?=$(RG_ZIDAR_DIR)/tools/bin/$(OS)/genie $(EXTRA_GENIE_ARGS) --zidar-path=$(RG_ZIDAR_DIR)
NINJA?=$(RG_ZIDAR_DIR)/tools/bin/$(OS)/ninja

.PHONY: help

clean:   ## Clean all intermediate files.
	@echo Cleaning...
	-@rm -rf .zidar

projgen: ## Generate project files for all configurations.
	@echo Generating project files...
	echo $(CURDIR)
	$(GENIE) --with-samples --with-unittests --with-tools vs2022 --file $(CURDIR)/zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --gcc=linux-clang   gmake --file zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --gcc=linux-gcc     gmake --file zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --gcc=osx-arm64     gmake --file zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --xcode=osx         xcode9 --file zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --xcode=ios         xcode9 --file zidar/zidar.lua
	$(GENIE) --with-samples --with-unittests --with-tools --gcc=android-arm64 gmake --file zidar/zidar.lua
