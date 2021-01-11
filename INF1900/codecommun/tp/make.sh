#!/bin/bash

cd libstatic
make clean
make

cd ../execdir
make clean
make
