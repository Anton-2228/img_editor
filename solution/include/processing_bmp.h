#ifndef PROCESSINC_BMP
#define PROCESSINC_BMP
#include "../include/image_inter.h"
#include "processing_errors/processing_bmp_errors.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum read_status read_from_bmp(struct image* img, char* source);

enum write_status write_to_bmp(struct image const* img, char* source);

#endif
