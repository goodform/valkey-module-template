#!/bin/bash

ROOT_DIR=`pwd`
VALKEY_DIR=$ROOT_DIR/thirdparty/valkey
VALKEY_SERVER_PATH=$VALKEY_DIR/src/valkey-server
TEST_DIR=$ROOT_DIR/tests/unit
PROJECT_NAME=valkeyexample
LIBRARY_NAME="lib"$PROJECT_NAME".so"

git submodule update --init --recursive

cd $VALKEY_DIR

make -j8

cd $TEST_DIR

python3 -m pip install -r requirements.txt
python3 -m pip install -e git+https://github.com/artikell/valkey-module-test.git@main#egg=vkmtest

export VALKEY_PATH=$VALKEY_SERVER_PATH
export VALKEY_MODULE_PATH=$ROOT_DIR/build/$LIBRARY_NAME

python3 main.py