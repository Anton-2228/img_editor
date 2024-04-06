//
// Created by user on 06.04.24.
//

#ifndef IMG_EDITOR_PROCESSING_SELECT_COMMAND_H
#define IMG_EDITOR_PROCESSING_SELECT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>

enum select_command_status  {
    SELECT_OK = 0,
    SELECT_ERROR,
    /* коды других ошибок  */
};

void processing_select_command_status(enum select_command_status status);

#endif //IMG_EDITOR_PROCESSING_SELECT_COMMAND_H
