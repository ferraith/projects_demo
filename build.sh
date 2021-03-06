#!/bin/bash

# Supported build configurations:
# demo.bin - debug/ARM:    make demo.bin BUILD_TYPE=debug PLATFORM=ARM
# demo.bin - release/ARM:  make demo.bin BUILD_TYPE=release PLATFORM=ARM
# demo.elf - debug/ARM:    make demo.elf BUILD_TYPE=debug PLATFORM=ARM
# demo.elf - release/ARM:  make demo.elf BUILD_TYPE=release PLATFORM=ARM
# demo.hex - debug/ARM:    make demo.hex BUILD_TYPE=debug PLATFORM=ARM
# demo.hex - release/ARM:  make demo.hex BUILD_TYPE=release PLATFORM=ARM
# demo.srec - debug/ARM:   make demo.srec BUILD_TYPE=debug PLATFORM=ARM
# demo.srec - release/ARM: make demo.srec BUILD_TYPE=release PLATFORM=ARM

project='demo'

options[0]='-s'

build_types[0]='debug'
build_types[1]='release'

platforms[0]='ARM'
platforms[1]='x86'

binary_formats[0]='elf'
binary_formats[1]='hex'
binary_formats[2]='bin'
binary_formats[3]='srec'

#
# Checks if passed command line arguments are valid
#
function CheckInputArgs {
    local ArgsAreValid=false
    for i in ${options[@]}; do
        if [ "$i" == "$option" ] || [ "$option" == "" ]; then
            for j in ${build_types[@]}; do
                if [ "$j" == "$build_type" ]; then
                    for k in ${platforms[@]}; do
                        if [ "$k" == "$platform" ]; then
                            for l in ${binary_formats[@]}; do
                                if [ "$l" == "$binary_format" ]; then
                                    ArgsAreValid=true
                                    break
                                fi
                            done
                        fi
                    done
                fi
            done
        fi
    done
    echo $ArgsAreValid
}

#
# Executes make with passed build configuration
#
function build {
    make $option clean_all
    echo
    make $option $project.$binary_format BUILD_TYPE=$build_type PLATFORM=$platform
}


# Check number of command line arguments
if [ "$#" -gt 2 ]; then
    # If first argument starts with "-", it's a option
    if [ ${1::1} == "-" ]; then
        option="$1"
        build_type="$2"
        platform="$3"
        binary_format="$4"
    else # No option is passed
        build_type="$1"
        platform="$2"
        binary_format="$3"
    fi
fi

# If no arguments are passed, use default configuration
if [ "$#" -eq 0 ]; then
    option="-s"
    build_type="debug"
    platform="ARM"
    binary_format="elf"
    build
# If arguments are passed, check if they are valid and start build
elif $(CheckInputArgs); then
    build
# If arguments are invalid, cancel build
else
    echo "Invalid build configuration"
fi
