#!/bin/bash
mydir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd)"
cd "${mydir}" && rm -rf build && mkdir build && cd build && cmake ./.. -DENABLE_ZCHAFF=ON && make && cd ..
