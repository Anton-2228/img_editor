//
// Created by user on 06.04.24.
//

#ifndef IMG_EDITOR_SEPIA_FILTER_H
#define IMG_EDITOR_SEPIA_FILTER_H
#include "image_inter.h"
#include "processing_errors/processing_sepia_filter_errors.h"
#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>

//extern void sepia_filter_asm(struct image* img, struct image* new_img);

enum sepia_filter_status sepia_filter(const struct image* img, struct image* new_img, char** argv);

#endif //IMG_EDITOR_SEPIA_FILTER_H
