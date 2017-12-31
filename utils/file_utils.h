#ifndef LIBSODIUM_FILE_CRYPTER_FILE_UTILS_H
#define LIBSODIUM_FILE_CRYPTER_FILE_UTILS_H

#include <stdbool.h>

bool check_if_file_exists(const char *filePath);

bool check_if_file_is_readable(const char *filePath);

bool check_if_file_is_writable(const char *filePath);

bool are_two_file_paths_the_same(const char *filePath1, const char *filePath2);

#endif //LIBSODIUM_FILE_CRYPTER_FILE_UTILS_H
