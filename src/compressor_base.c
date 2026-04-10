#include "../include/compressor_base.h"

#include <stdlib.h>

struct compressor
{
  const char *name;
  signed int (*compress)(FILE *out, FILE *in);
  signed int (*decompress)(FILE *out, FILE *in);
};

struct compressor *init_compressor(
    const char *name,
    signed int (*compress)(FILE *out, FILE *in),
    signed int (*decompress)(FILE *out, FILE *in)
  )
{
  struct compressor *self = malloc(sizeof(struct compressor));

  self->name = name;
  self->compress = compress;
  self->decompress = decompress;

  return self;
}

void free_compressor(struct compressor *self)
{
  free(self);
}

const char *compressor_get_name(struct compressor *self)
{
  return self->name;
}

signed int compressor_compress(struct compressor *self, FILE *out, FILE *in)
{
  return self->compress(out, in);
}

signed int compressor_decompress(struct compressor *self, FILE *out, FILE *in)
{
  return self->decompress(out, in);
}
