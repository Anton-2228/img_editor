#include "../../include/processing_errors/processing_select_command_errors.h"

char* errors_select_command_text[] = {
        [SELECT_ERROR] = "Название команды введено неверно",
};

void processing_select_command_status(enum select_command_status status) {
    if (status != SELECT_OK) {
        fprintf(stderr, "%s \n", errors_select_command_text[status]);
        exit(EXIT_FAILURE);
    }
}
