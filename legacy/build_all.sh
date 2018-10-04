#!/bin/bash

./clean.sh
./build_os.sh $1
./build_iso.sh