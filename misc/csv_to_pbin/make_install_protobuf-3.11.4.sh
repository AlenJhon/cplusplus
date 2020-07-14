#!/bin/bash

cur_dir="$(cd $(dirname $0); pwd)"
echo "install path : ${cur_dir} ..."

#cd ${cur_dir}"/src"
tar -zxf protobuf-3.11.4.tar.gz

cd protobuf-3.11.4
make clean
./autogen.sh
./configure --disable-dependency-tracking --enable-static --disable-shared --prefix=`pwd`/install/protobuf-3.11.4
make -j 8
make install
