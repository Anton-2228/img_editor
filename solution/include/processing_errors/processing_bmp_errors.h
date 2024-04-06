#ifndef IMAGE_TRANSFORMER_PROCESSING_BMP_ERRORS_H
#define IMAGE_TRANSFORMER_PROCESSING_BMP_ERRORS_H

#include <stdio.h>
#include <stdlib.h>

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    ALLOCATE_ERROR,
    /* коды других ошибок  */
};

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

void processing_read_status(enum read_status status);

void processing_write_status(enum write_status status);

#endif //IMAGE_TRANSFORMER_PROCESSING_BMP_ERRORS_H
