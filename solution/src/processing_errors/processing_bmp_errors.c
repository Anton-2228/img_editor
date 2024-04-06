#include "../../include/processing_errors/processing_bmp_errors.h"

char* errors_read_text[] = {
        [READ_INVALID_HEADER] = "Проблема с хедером",
        [READ_INVALID_BITS] = "Проблема с чтением пикселя",
        [READ_INVALID_SIGNATURE] = "Такого файла не существует",
        [ALLOCATE_ERROR] = "Malloc не смог аллоцировать память",
};

char* errors_write_text[] = {
        [WRITE_ERROR] = "Ошибка записи в файл",
};

void processing_read_status(enum read_status status) {
    if (status != READ_OK) {
        fprintf(stderr, "%s \n", errors_read_text[status]);
        exit(EXIT_FAILURE);
    }
}

void processing_write_status(enum write_status status) {
    if (status != WRITE_OK) {
        fprintf(stderr, "%s \n", errors_write_text[status]);
        exit(EXIT_FAILURE);
    }
}
