//
// Created by anton on 03.12.23.
//

#ifndef IMAGE_TRANSFORMER_PROCESSING_ROTATE_ERRORS_H
#define IMAGE_TRANSFORMER_PROCESSING_ROTATE_ERRORS_H

#include <stdio.h>
#include <stdlib.h>

enum rotate_status  {
    ROTATE_OK = 0,
    ROTATE_ERROR
};

void processing_rotate_status(enum rotate_status status);

#endif //IMAGE_TRANSFORMER_PROCESSING_ROTATE_ERRORS_H
