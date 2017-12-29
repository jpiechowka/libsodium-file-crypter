cmake_minimum_required(VERSION 3.9)
project(libsodium-file-crypter C)

set(CMAKE_C_STANDARD 11)

# Find libsodium
FIND_PATH(LIBSODIUM_INCLUDE_DIR NAMES sodium.h PATHS /usr/include/ /usr/local/include/)
FIND_LIBRARY(LIBSODIUM_LIBRARY NAMES sodium libsodium PATHS /usr/lib /usr/local/lib)
IF (LIBSODIUM_INCLUDE_DIR AND LIBSODIUM_LIBRARY)
    SET(LIBSODIUM_FOUND TRUE)
ENDIF (LIBSODIUM_INCLUDE_DIR AND LIBSODIUM_LIBRARY)

IF (LIBSODIUM_FOUND)
    IF (NOT LIBSODIUM_FIND_QUIETLY)
        MESSAGE(STATUS "Found libsodium:")
        MESSAGE(STATUS "  (Headers)       ${LIBSODIUM_INCLUDE_DIR}")
        MESSAGE(STATUS "  (Library)       ${LIBSODIUM_LIBRARY}")
    ENDIF (NOT LIBSODIUM_FIND_QUIETLY)
ELSE (LIBSODIUM_FOUND)
    MESSAGE(FATAL_ERROR "Could not find libsodium")
ENDIF (LIBSODIUM_FOUND)

add_executable(
        libsodium-file-crypter
        main.c
        crypto/initialize_libsodium.c crypto/initialize_libsodium.h
        utils/logger.c utils/logger.h
)

target_link_libraries(libsodium-file-crypter ${LIBSODIUM_LIBRARY})
