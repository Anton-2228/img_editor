#ifndef ROTATE
#define ROTATE
#include "../include/image_inter.h"
#include "processing_errors/processing_rotate_errors.h"
#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>

enum rotate_status rotate(const struct image* img, struct image* new_img, char** argv);

#endif
