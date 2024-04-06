#include "../include/rotate.h"

struct image rotate_0(const struct image* img);
struct image rotate_90(const struct image* img);
struct image rotate_180(const struct image* img);
struct image rotate_270(const struct image* img);

typedef struct image (*angel_func)(const struct image* img);

struct angels_rotate {
    int16_t angel;
    angel_func func;
};

const struct angels_rotate angels[] = {
        {0, rotate_0},
        {90, rotate_90},
        {-90, rotate_270},
        {180, rotate_180},
        {-180, rotate_180},
        {270, rotate_270},
        {-270, rotate_90},
};

enum rotate_status rotate(const struct image* img, struct image* new_img, char** argv) {
    char* end;
    long val = strtol(argv[4], &end, 10);
    int16_t angel = (int16_t)val;
    for (size_t i = 0; i < sizeof(angels)/sizeof(angels[0]); i++) {
        if (angels[i].angel == angel) {
            *new_img = angels[i].func(img);
            return ROTATE_OK;
        }
    }
    return ROTATE_ERROR;
}

struct image create_new_img(uint64_t new_width, uint64_t new_height) {
    struct pixel* new_data = malloc(sizeof(struct pixel) * new_width * new_height);
    struct image new_img = (struct image) {.width = new_width, .height = new_height, .data = new_data};
    return new_img;
}

struct image rotate_0(const struct image* img) {
    struct image new_img = create_new_img(img -> width, img -> height);
    struct pixel pixel;
    for (size_t i = 0; i < img -> height; i++) {
        for (size_t z = 0; z < img -> width; z++) {
            pixel = img -> data[img -> width * i + z];
            new_img.data[img -> width * i + z] = pixel;
        }
    }
    return new_img;
}

struct image rotate_90(const struct image* img) {
    struct image new_img = create_new_img(img -> height, img -> width);

    struct pixel pixel;
    for (size_t i = 1; i <= img -> height; i++) {
        for (size_t z = 1; z <= img -> width; z++) {
            pixel = img -> data[img -> width * (i-1) + (z-1)];
            new_img.data[img -> height * img -> width - (z * img -> height - i) - 1] = pixel;
        }
    }
    return new_img;
}

struct image rotate_270(const struct image* img) {
    struct image new_img = create_new_img(img -> height, img -> width);

    struct pixel pixel;
    for (size_t i = 1; i <= img -> height; i++) {
        for (size_t z = 1; z <= img -> width; z++) {
            pixel = img -> data[img -> width * (i-1) + (z-1)];
            new_img.data[z * img -> height - i] = pixel;
        }
    }
    return new_img;
}

struct image rotate_180(const struct image* img) {
    struct image new_img = create_new_img(img -> width, img -> height);

    struct pixel pixel;
    for (size_t i = 0; i < img -> height; i++) {
        for (size_t z = 0; z < img -> width; z++) {
            pixel = img -> data[img -> width * i + z];
            new_img.data[(img -> height - i) * img -> width - z - 1] = pixel;
        }
    }

    return new_img;
}
