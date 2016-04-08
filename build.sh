#!/bin/bash

# Usage:
# $ ./build.sh ./hello-world

mkdir ./build -p
pushd build >& /dev/null

cmake ..

make

popd >& /dev/null

# If arguments are supplied to the build script, then this could mean
# that the user either wants to install the project or execute a program
if [ $# -gt 0 ]; then
    # The user wants to install the project
    if [ $1 == "install" ]; then
        make install
    else
        # The user wants to execute a script in the bin directory
        # Move the bin directory and pass the command to call
        # Example call: ./build.sh ./hello-world
        pushd ./bin >& /dev/null
        $1
        popd >& /dev/null
    fi
fi
