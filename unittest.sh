#!/bin/bash
mkdir bin
rm -rf bin/*
cd bin
cmake ..
make
cd ..
bin/unittests
