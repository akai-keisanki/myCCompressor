#include "../../include/compressors/rle.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void rle_write_raw(FILE *out, char *raw, unsigned char count)
{
  putc(count, out);
  fwrite(raw, sizeof(char), count, out);
}

void rle_write_run(FILE *out, char run, unsigned char count)
{
  putc(count | 1 << 7, out);
  putc(run, out);
}

signed int rle_compress(FILE *out, FILE *in)
{
  signed int c;
  signed int prev = getc(in);
  char raw[0xFF];
  unsigned char count = 1;
  bool run = 0;

  while (prev != EOF)
  {
    c = getc(in);

    if (c == prev)
    {
      if (run)
        if (count < (1 << 7) - 1)
          ++count;
        else
        {
          rle_write_run(out, prev, count);
          count = 1;
        }
      else
      {
        raw[count - 1] = prev;
        rle_write_raw(out, raw, count);

        count = 1;
      }

      run = true;
    }
    else
    {
      if (!run)
      {
        raw[count - 1] = prev;

        if (count < (1 << 7) - 1)
          ++count;
        else
        {
          rle_write_raw(out, raw, count);
          count = 1;
        }
      }
      else
      {
        rle_write_run(out, prev, count);

        count = 1;
      }

      run = false;
    }

    prev = c;
  }

  if (run)
    rle_write_run(out, prev, count);
  else
    rle_write_raw(out, raw, count - 1);

  return EXIT_SUCCESS;
}

signed int rle_decompress(FILE *out, FILE *in)
{
  signed int c;
  signed int count;

  while ((count = getc(in)) != EOF)
  {
    if (count & (1 << 7))
    {
      count &= (1 << 7) - 1;

      if ((c = getc(in)) == EOF)
        return EXIT_FAILURE;

      for (size_t i = 0; i < count; ++i)
        putc(c, out);
    }
    else
      for (size_t i = 0; i < count; ++i)
        if ((c = getc(in)) != EOF)
          putc(c, out);
        else
          return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

struct compressor *init_rle_compressor(void)
{
  return init_compressor("rle", rle_compress, rle_decompress);
}
