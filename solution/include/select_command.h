//
// Created by user on 06.04.24.
//

#ifndef IMG_EDITOR_SELECT_COMMAND_H
#define IMG_EDITOR_SELECT_COMMAND_H
#include "rotate.h"
#include "sepia_filter.h"
#include "processing_errors/processing_select_command_errors.h"
#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//typedef enum sepia_filter_status (*command_func)(const struct image* img, struct struct image* new_img, char** argv);
typedef int (*command_func)(const struct image* img, struct image* new_img, char** argv);
typedef void (*processing_status_command)(int status);

enum select_command_status select_command(char* command, const struct image* img, struct image* new_img, char** argv);

#endif //IMG_EDITOR_SELECT_COMMAND_H
