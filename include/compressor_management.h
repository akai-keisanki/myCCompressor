#ifndef MYCCOMPRESSOR_COMPRESSOR_MANAGEMENT_H
#define MYCCOMPRESSOR_COMPRESSOR_MANAGEMENT_H

#include "../include/compressor_base.h"

signed int init_compressors(void);
void free_compressors(void);

signed int load_compressors(void);

struct compressor *get_compressor(const char *name);

signed int push_to_compressor_list(struct compressor *compressor);

#endif
