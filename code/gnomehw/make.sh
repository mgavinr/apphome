#!/bin/bash

set -e
set -x

if [[ $# -eq $# ]]; then
    pushd cmake-build-debug

    echo "-------------------- CONAN SETUP/BUILD -----------------------" > /dev/null
    echo "-------------------- CMAKE SETUP -----------------------" > /dev/null
    echo "-------------------- CMAKE BUILD -----------------------" > /dev/null
    cmake --build .
    ./bin/gnomehw
    popd
fi

if [[ $# -gt 0 ]]; then
    rm -rf cmake-build-release
    mkdir cmake-build-release
    git checkout cmake-build-debug/.gitignore
    pushd cmake-build-release

    echo "-------------------- CONAN SETUP/BUILD -----------------------" > /dev/null
    echo "-------------------- CMAKE SETUP -----------------------" > /dev/null
    echo "-------------------- CMAKE BUILD -----------------------" > /dev/null
    cmake --build .

    echo "-------------------- RUN" > /dev/null
    ./bin/gnomehw
fi
