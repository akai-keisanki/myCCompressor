#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/compressor_base.h"
#include "../include/compressor_management.h"

signed int main(signed int argc, char **argv)
{
  struct compressor *compressor;

  if (argc < 3)
  {
    fputs("Insufficient arguments.", stderr);
    return EXIT_FAILURE;
  }

  if (load_compressors())
    return EXIT_FAILURE;

  if (!(compressor = get_compressor(argv[1])))
    goto failure_exit;

  if (!strcmp(argv[2], "compress"))
  {
    if (compressor_compress(compressor, stdout, stdin))
    {
      fputs("Compression error.", stderr);
      goto failure_exit;
    }
  }
  else if (!strcmp(argv[2], "decompress"))
  {
    if (compressor_decompress(compressor, stdout, stdin))
    {
      fputs("Decompression error.", stderr);
      goto failure_exit;
    }
  }
  else
  {
    fputs("Unknown option.", stderr);
    goto failure_exit;
  }
  
  fputs("Exiting successfully.", stderr);

  free_compressors();

  return EXIT_SUCCESS;

failure_exit:

  free_compressors();

  return EXIT_FAILURE;
}
