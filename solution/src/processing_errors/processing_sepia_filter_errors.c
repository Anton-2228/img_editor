#include "../../include/processing_errors/processing_sepia_filter_errors.h"

char* errors_sepia_filter_text[] = {

};

void processing_sepia_filter_status(enum sepia_filter_status status) {
    if (status != SEPIA_FILTER_OK) {
        fprintf(stderr, "%s \n", errors_sepia_filter_text[status]);
        exit(EXIT_FAILURE);
    }
}
