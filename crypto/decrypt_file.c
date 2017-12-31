#include <stdio.h>
#include <memory.h>
#include "decrypt_file.h"
#include "initialize_libsodium.h"
#include "../utils/logger.h"
#include "../utils/file_utils.h"

int decrypt_file(const char *fileToDecrypt, const char *outputFile, const char *password) {
    //Try to initialize libsodium before doing anything else. If this fails the program will exit.
    initialize_libsodium();

    //Generating key from supplied password
    unsigned char salt[SALT_LEN];
    unsigned char generatedCryptoKey[KEY_LEN];

    //TODO figure out a better way to generate and store salt instead of all zeros
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

    //Check if file to decrypt exists and is readable
    if (!(check_if_file_exists(fileToDecrypt) && check_if_file_is_readable(fileToDecrypt))) {
        log_error_concat_str(fileToDecrypt, " file does not exists");
        return 1;
    } else {
        log_debug_concat_str(fileToDecrypt, " file exists and is readable");
    }

    // Decrypting file
    log_info_concat_str("Starting decryption of file: ", fileToDecrypt);
    log_info_concat_str("Decrypted file will be saved as: ", outputFile);

    unsigned char bufferIn[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char bufferOut[CHUNK_SIZE];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_state st;
    FILE *openOutputFile, *openFileToDecrypt;
    unsigned long long outputLen;
    size_t readLen;
    int eof;
    int ret = -1;
    unsigned char tag;

    log_debug("Opening file to decrypt in rb mode");
    openFileToDecrypt = fopen(fileToDecrypt, "rb");
    log_debug("Opening output file in wb mode");
    openOutputFile = fopen(outputFile, "wb");
    fread(header, 1, sizeof header, openFileToDecrypt);
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, generatedCryptoKey) != 0) {
        goto ret; /* incomplete header */
    }
    do {
        readLen = fread(bufferIn, 1, sizeof bufferIn, openFileToDecrypt);
        eof = feof(openFileToDecrypt);
        if (crypto_secretstream_xchacha20poly1305_pull(&st, bufferOut, &outputLen, &tag,
                                                       bufferIn, readLen, NULL, 0) != 0) {
            log_error("Corrupted chunk encountered");
            goto ret; /* corrupted chunk */
        }
        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL && !eof) {
            log_error("Premature end (end of file to decrypt reached before the end of the stream)");
            goto ret; /* premature end (end of openFileToDecrypt reached before the end of the stream) */
        }
        fwrite(bufferOut, 1, (size_t) outputLen, openOutputFile);
    } while (!eof);

    ret = 0;
    ret:
    {

    };
    log_debug("Closing open output file");
    fclose(openOutputFile);
    log_debug("Closing open file to decrypt");
    fclose(openFileToDecrypt);

    //Zero out key in memory
    log_debug("Zeroing crypto key in memory using sodium_memzero() function");
    sodium_memzero(generatedCryptoKey, sizeof(generatedCryptoKey));
    log_info("File decryption finished");

    return ret;
}
