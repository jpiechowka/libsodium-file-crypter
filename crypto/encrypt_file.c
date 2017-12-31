#include <stdio.h>
#include <memory.h>
#include "encrypt_file.h"
#include "initialize_libsodium.h"
#include "../utils/logger.h"
#include "../utils/file_utils.h"

int encrypt_file(const char *fileToEncrypt, const char *outputFile, const char *password) {
    //Try to initialize libsodium before doing anything else. If this fails the program will exit.
    initialize_libsodium();

    //Generating key from supplied password
    unsigned char salt[SALT_LEN];
    unsigned char generatedCryptoKey[KEY_LEN];

    //TODO: figure out a better way to generate and store salt instead of all zeros
    log_debug("Generating salt");
    sodium_memzero(salt, sizeof(salt));

    log_debug_concat_str("Generating cryptographic key from password: ", password);

    if (crypto_pwhash(generatedCryptoKey, sizeof generatedCryptoKey, password, strlen(password), salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        log_error("Error when running Argon2, out of memory");
        return 1;
    } else {
        log_debug("Key generated successfully");
    }

    //Check if file to encrypt exists and is readable
    if (!(check_if_file_exists(fileToEncrypt) && check_if_file_is_readable(fileToEncrypt))) {
        log_error_concat_str(fileToEncrypt, " file does not exists");
        return 1;
    } else {
        log_debug_concat_str(fileToEncrypt, " file exists and is readable");
    }

    // Encrypting file
    log_info_concat_str("Starting encryption of file: ", fileToEncrypt);
    log_info_concat_str("Encrypted file will be saved as: ", outputFile);

    unsigned char bufferIn[CHUNK_SIZE];
    unsigned char bufferOut[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_state st;
    FILE *openOutputFile, *openFileToEncrypt;
    unsigned long long outputLen;
    size_t readLen;
    int eof;
    unsigned char tag;

    log_debug("Opening file to encrypt in rb mode");
    openFileToEncrypt = fopen(fileToEncrypt, "rb");
    log_debug("Opening output file in wb mode");
    openOutputFile = fopen(outputFile, "wb");
    crypto_secretstream_xchacha20poly1305_init_push(&st, header, generatedCryptoKey);
    fwrite(header, 1, sizeof header, openOutputFile);
    do {
        readLen = fread(bufferIn, 1, sizeof bufferIn, openFileToEncrypt);
        eof = feof(openFileToEncrypt);
        tag = eof ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;
        crypto_secretstream_xchacha20poly1305_push(&st, bufferOut, &outputLen, bufferIn, readLen,
                                                   NULL, 0, tag);
        fwrite(bufferOut, 1, (size_t) outputLen, openOutputFile);
    } while (!eof);

    log_debug("Closing open output file");
    fclose(openOutputFile);
    log_debug("Closing open file to encrypt");
    fclose(openFileToEncrypt);

    //Zero out key in memory
    log_debug("Zeroing crypto key in memory using sodium_memzero() function");
    sodium_memzero(generatedCryptoKey, sizeof(generatedCryptoKey));
    log_info("File encryption finished");

    return 0;
}
