#include <stdio.h>
#include "encrypt_file.h"

#define CHUNK_SIZE 4096

int encrypt_file(const char *fileToEncrypt, const char *outputFile,
                 const unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES]) {

    unsigned char buf_in[CHUNK_SIZE];
    unsigned char buf_out[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_state st;
    FILE *openOutputFile, *openFileToEncrypt;
    unsigned long long out_len;
    size_t rlen;
    int eof;
    unsigned char tag;

    openFileToEncrypt = fopen(fileToEncrypt, "rb");
    openOutputFile = fopen(outputFile, "wb");
    crypto_secretstream_xchacha20poly1305_init_push(&st, header, key);
    fwrite(header, 1, sizeof header, openOutputFile);
    do {
        rlen = fread(buf_in, 1, sizeof buf_in, openFileToEncrypt);
        eof = feof(openFileToEncrypt);
        tag = eof ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;
        crypto_secretstream_xchacha20poly1305_push(&st, buf_out, &out_len, buf_in, rlen,
                                                   NULL, 0, tag);
        fwrite(buf_out, 1, (size_t) out_len, openOutputFile);
    } while (!eof);
    fclose(openOutputFile);
    fclose(openFileToEncrypt);
    return 0;
}
