#include <stdio.h>
#include "decrypt_file.h"
#include "initialize_libsodium.h"

int decrypt_file(const char *fileToDecrypt, const char *outputFile,
                 const unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES]) {

    //Try to initialize libsodium before doing anything else. If this fails the program will exit.
    initialize_libsodium();

    unsigned char buf_in[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char buf_out[CHUNK_SIZE];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_state st;
    FILE *openOutputFile, *openFileToDecrypt;
    unsigned long long out_len;
    size_t rlen;
    int eof;
    int ret = -1;
    unsigned char tag;

    openFileToDecrypt = fopen(fileToDecrypt, "rb");
    openOutputFile = fopen(outputFile, "wb");
    fread(header, 1, sizeof header, openFileToDecrypt);
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, key) != 0) {
        goto ret; /* incomplete header */
    }
    do {
        rlen = fread(buf_in, 1, sizeof buf_in, openFileToDecrypt);
        eof = feof(openFileToDecrypt);
        if (crypto_secretstream_xchacha20poly1305_pull(&st, buf_out, &out_len, &tag,
                                                       buf_in, rlen, NULL, 0) != 0) {
            goto ret; /* corrupted chunk */
        }
        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL && !eof) {
            goto ret; /* premature end (end of openFileToDecrypt reached before the end of the stream) */
        }
        fwrite(buf_out, 1, (size_t) out_len, openOutputFile);
    } while (!eof);

    ret = 0;
    ret:
    fclose(openOutputFile);
    fclose(openFileToDecrypt);
    return ret;
}
