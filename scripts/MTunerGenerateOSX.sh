#!/bin/bash
target="$1"

if [ -z "$target" ]; then
action="--gcc=osx-x64 gmake"
fi

cd ../src/MTuner/genie
../../../build/tools/bin/darwin/genie $action
cd ../../../srcipts

