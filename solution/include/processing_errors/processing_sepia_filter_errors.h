//
// Created by user on 06.04.24.
//

#ifndef IMG_EDITOR_PROCESSING_SEPIA_FILTER_ERRORS_H
#define IMG_EDITOR_PROCESSING_SEPIA_FILTER_ERRORS_H

#include <stdio.h>
#include <stdlib.h>

enum sepia_filter_status  {
    SEPIA_FILTER_OK = 0,
    /* коды других ошибок  */
};

void processing_sepia_filter_status(enum sepia_filter_status status);

#endif //IMG_EDITOR_PROCESSING_SEPIA_FILTER_ERRORS_H
