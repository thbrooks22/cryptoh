project(cryptoh_lib)

set(HEADER_FILES
        hash/sha/sha256.h
        )

set(SOURCE_FILES
        hash/sha/sha256.cpp
        )

add_library(cryptoh_lib SHARED ${SOURCE_FILES} ${HEADER_FILES})