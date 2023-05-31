project(cryptoh)

set(HEADER_FILES
        hash/sha/sha256.h
        util/math/gf28.h)

set(SOURCE_FILES
        hash/sha/sha256.cpp
        util/math/gf28.cpp)

add_library(cryptoh_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})