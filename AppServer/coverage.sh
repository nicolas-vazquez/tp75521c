#!/usr/bin/env bash

cd build/
make test

lcov --capture -z --directory src/ --output-file coverage.info
genhtml coverage.info --output-directory out

xdg-open out/index.html
