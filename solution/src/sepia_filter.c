#include "sepia_filter.h"

extern void sepia_filter_asm(const struct image* img, struct image* new_img);

struct image create_new_img1(const struct image* img) {
    struct pixel* new_data = malloc(sizeof(struct pixel) * img->width * img->height);
    struct image new_img = (struct image) {.width = img->width, .height = img->height, .data = new_data};
    return new_img;
}

enum sepia_filter_status sepia_filter(const struct image* img, struct image* new_img, char** argv) {
    *new_img = create_new_img1(img);
    sepia_filter_asm(img, new_img);
    return SEPIA_FILTER_OK;
}
