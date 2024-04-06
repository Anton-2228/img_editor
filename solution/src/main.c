//#include "../include/rotate.h"
#include "../include/select_command.h"
#include "../include/processing_bmp.h"
#include <stdlib.h>

int main( int argc, char** argv ) {
    (void) argc; (void) argv;

    struct image img;
    enum read_status read_pic_status = read_from_bmp(&img, argv[1]);
    processing_read_status(read_pic_status);

    struct image new_img;
    //char* end;
    //long val = strtol(argv[3], &end, 10);
    //enum rotate_status rotate_pic_status = rotate(&img, &new_img, (int16_t)val);
    enum select_command_status select_status = select_command(argv[3], &img, &new_img, argv);
    if (img.data != NULL) {
        free(img.data);
    }
    //processing_rotate_status(rotate_pic_status);
    processing_select_command_status(select_status);

    enum  write_status write_pic_status = write_to_bmp(&new_img, argv[2]);
    processing_write_status(write_pic_status);

    return 0;
}
