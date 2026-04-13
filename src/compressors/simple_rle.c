#include "../../include/compressors/simple_rle.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

signed int simple_rle_compress(FILE *out, FILE *in)
{
  signed int c;
  signed int prev = getc(in);
  unsigned char count = 1;

  while (prev != EOF)
  {
    c = getc(in);

    if (c == prev && count < 0xFF)
      ++count;
    else
    {
      putc(prev, out);
      putc(count, out);

      count = 1;
    }

    prev = c;
  }

  return EXIT_SUCCESS;
}

signed int simple_rle_decompress(FILE *out, FILE *in)
{
  int c;
  unsigned char count;

  while ((c = getc(in)) != EOF)
  {
    if ((count = getc(in)) == EOF)
      return EXIT_FAILURE;
    
    for (size_t i = 0; i < count; ++i)
      putc(c, out);
  }

  return EXIT_SUCCESS;
}

struct compressor *init_simple_rle_compressor(void)
{
  return init_compressor("simple_rle", simple_rle_compress, simple_rle_decompress);
}
