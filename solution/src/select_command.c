//
// Created by user on 06.04.24.
//

#include "select_command.h"

struct command_func {
    char* title;
    command_func func;
    processing_status_command processing_status;
};

const struct command_func commands[] = {
        {"rotate", (command_func)rotate, (processing_status_command)processing_rotate_status},
        {"sepia_filter", (command_func)sepia_filter, (processing_status_command)processing_sepia_filter_status},
};

enum select_command_status select_command(char* command, const struct image* img, struct image* new_img, char** argv) {
    for (size_t i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
        if (strcmp(commands[i].title, command) == 0) {
            int status = commands[i].func(img, new_img, argv);
            commands[i].processing_status(status);
            return SELECT_OK;
        }
    }
    return SELECT_ERROR;
}