#!/bin/bash

CC_FLAGS_REL="-O3 -march=native -DNDEBUG"
CC_FLAGS_DBG="-g3"
CC_FLAGS="-std=c99 -Wall -Wextra"
if [ -n "$REL" ]
then
    CC_FLAGS="$CC_FLAGS $CC_FLAGS_REL"
else
    CC_FLAGS="$CC_FLAGS $CC_FLAGS_DBG"
fi

SRC_FILES="../stringsort/lines.c ../stringsort/file.c ../stringsort/string_helper.c ../stringsort/stringsort.c ../stringsort/util.c"

gcc $CC_FLAGS $SRC_FILES -o stringsort
