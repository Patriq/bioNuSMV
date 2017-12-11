#!/bin/bash
mydir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd)"
cd "${mydir}" && cd build && make && cd ..
