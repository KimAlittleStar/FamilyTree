#! /bin/bash
#执行 make
mingw32-make.exe target=$1 TYPE=$2 PREDEF="_DEBUG MEMWATCH MW_STDIO"

#执行可执行文件
./$1
