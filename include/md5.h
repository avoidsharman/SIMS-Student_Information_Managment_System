#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include <stddef.h>
#include "common.h"

typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    uint8_t buffer[64];
} MD5_CTX;

void md5_init(MD5_CTX *ctx);
void md5_update(MD5_CTX *ctx, const uint8_t *input, size_t inputLen);
void md5_final(uint8_t digest[16], MD5_CTX *ctx);
void md5_hash_string(const char *input, char output[MD5_HEX_SIZE]);
void md5_hash_buffer(const uint8_t *input, size_t len, char output[MD5_HEX_SIZE]);

#endif
