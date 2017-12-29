#ifndef LIBSODIUM_FILE_CRYPTER_DECRYPT_FILE_H
#define LIBSODIUM_FILE_CRYPTER_DECRYPT_FILE_H

#include <sodium.h>

#define CHUNK_SIZE 4096 // Make sure that CHUNK_SIZE is the same as in the encrypt_file.h

int decrypt_file(const char *fileToDecrypt, const char *outputFile,
                 const unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES]);

#endif //LIBSODIUM_FILE_CRYPTER_DECRYPT_FILE_H
