#ifndef MYCCOMPRESSOR_COMPRESSOR_BASE_H
#define MYCCOMPRESSOR_COMPRESSOR_BASE_H

#include <stdio.h>

struct compressor;

struct compressor *init_compressor(
    const char *name,
    signed int (*compress)(FILE *out, FILE *in),
    signed int (*decompress)(FILE *out, FILE *in)
  );
void free_compressor(struct compressor *self);

const char *compressor_get_name(struct compressor *self);

signed int compressor_compress(struct compressor *self, FILE *out, FILE *in);
signed int compressor_decompress(struct compressor *self, FILE *out, FILE *in);

#endif
