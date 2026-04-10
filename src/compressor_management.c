#include "../include/compressor_management.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compressor_includes.def"

#define COMPRESSORS_SIZE 0x100

struct compressor **compressors = NULL;
size_t compressor_count;

signed int init_compressors(void)
{
  compressors = malloc(sizeof(struct compressor *) * COMPRESSORS_SIZE);

  if (!compressors)
    return EXIT_FAILURE;

  compressor_count = 0;

  return EXIT_SUCCESS;
}

void free_compressors(void)
{
  for (size_t i = 0; i < compressor_count; ++i)
    free_compressor(compressors[i]);

  free(compressors);
}

signed int load_compressors(void)
{
  if (!compressors)
    if (init_compressors())
    {
      fputs("Compressor list could not be initialized. Could not load compressors.", stderr);
      return EXIT_FAILURE;
    }


  #define ADD_COMPRESSOR(name) push_to_compressor_list(init_##name##_compressor());
  #include "compressor_list.def"
  #undef ADD_COMPRESSOR

  return EXIT_SUCCESS;
}

struct compressor *get_compressor(const char *name)
{
  for (size_t i = 0; i < compressor_count; ++i)
    if (!strcmp(compressor_get_name(compressors[i]), name))
      return compressors[i];

  fputs("Compressor could not be found.", stderr);
  return NULL;
}

signed int push_to_compressor_list(struct compressor *compressor)
{
  if (compressor_count >= COMPRESSORS_SIZE)
  {
    fputs("Compressor list is full. Could not push compressor.", stderr);
    return EXIT_FAILURE;
  }

  compressors[compressor_count++] = compressor;

  return EXIT_SUCCESS;
}
