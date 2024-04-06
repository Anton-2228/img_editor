#include "../../include/processing_errors/processing_rotate_errors.h"

char* errors_rotate_text[] = {
        [ROTATE_ERROR] = "Ошибка поворота"
};

void processing_rotate_status(enum rotate_status status) {
    if (status != ROTATE_OK) {
        fprintf(stderr, "%s \n", errors_rotate_text[status]);
        exit(EXIT_FAILURE);
    }
}
