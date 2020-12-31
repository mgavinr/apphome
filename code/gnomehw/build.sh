#!/bin/bash

set -e
set -x

rm -rf cmake-build-debug
mkdir cmake-build-debug
git checkout cmake-build-debug/.gitignore
pushd cmake-build-debug

echo "-------------------- CONAN SETUP/BUILD -----------------------" > /dev/null
conan install ..
echo "-------------------- CMAKE SETUP -----------------------" > /dev/null
cmake .. -DCMAKE_BUILD_TYPE=Debug
echo "-------------------- CMAKE BUILD -----------------------" > /dev/null
cmake --build .
./bin/gnomehw
popd

rm -rf cmake-build-release
mkdir cmake-build-release
git checkout cmake-build-debug/.gitignore
pushd cmake-build-release

echo "-------------------- CONAN SETUP/BUILD -----------------------" > /dev/null
conan install ..
echo "-------------------- CMAKE SETUP -----------------------" > /dev/null
cmake .. -DCMAKE_BUILD_TYPE=Release
echo "-------------------- CMAKE BUILD -----------------------" > /dev/null
cmake --build .

echo "-------------------- RUN" > /dev/null
./bin/gnomehw
