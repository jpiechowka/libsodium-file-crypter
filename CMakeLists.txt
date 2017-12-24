cmake_minimum_required(VERSION 3.9)
project(libsodium_file_crypter C)

set(CMAKE_C_STANDARD 11)

add_executable(libsodium_file_crypter main.c utils/logger.c utils/logger.h)