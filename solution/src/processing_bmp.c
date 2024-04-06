#include "../include/processing_bmp.h"

struct __attribute__((packed)) bmp_header
{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

enum read_status from_bmp_name(FILE** bmp_file, char* mode, char* name) {
    (*bmp_file) = fopen(name, mode);
    if ((*bmp_file) == NULL) {
        return READ_INVALID_SIGNATURE;
    }
    return READ_OK;
}

uint8_t calc_padding(uint32_t width, uint16_t bitCount) {
    return (4 - (width * (bitCount / 8)) % 4) % 4;;
}

enum read_status read_header(FILE* in, struct bmp_header* header) {
    size_t result = fread(header, sizeof(struct bmp_header), 1, in);
    if (result == 0) {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

enum read_status create_img_for_read(struct bmp_header* header, struct image* img) {
    struct pixel* data = malloc(sizeof(struct pixel) * header -> biWidth * header -> biHeight);
    if (data == NULL) {
        return ALLOCATE_ERROR;
    }
    *img = (struct image){.data = data, .height = header -> biHeight, .width = header -> biWidth};
    return READ_OK;
}

enum read_status read_pixels(FILE* in, struct bmp_header* header, struct image* img, uint8_t padding) {
    struct pixel* pixel = NULL;
    fseek(in, header -> bOffBits, SEEK_SET);
    for (size_t i = 0; i < header -> biHeight; i++) {
        for (size_t z = 0; z < header -> biWidth; z++) {
            pixel = img -> data + header -> biWidth * i + z;
            size_t result = fread(pixel, sizeof(struct pixel), 1, in);
            if (pixel == NULL || result != 1) {
                return READ_INVALID_BITS;
            }
        }
        fseek(in, padding, SEEK_CUR);
    }
    return READ_OK;
}

enum read_status from_bmp(FILE* in, struct image* img) {

    struct bmp_header header;
    enum read_status header_status = read_header(in, &header);
    if (header_status != READ_OK) {
        return header_status;
    }

    uint8_t padding = calc_padding(header.biWidth, header.biBitCount);

    enum read_status img_create_status = create_img_for_read(&header, img);
    if (img_create_status != READ_OK) {
        return img_create_status;
    }

    enum read_status pixels_status = read_pixels(in, &header, img, padding);
    if (pixels_status != READ_OK) {
        return img_create_status;
    }

    return READ_OK;
}

enum read_status read_from_bmp(struct image* img, char* source) {
    FILE* bmp_file = NULL;
    enum read_status file_status = from_bmp_name(&bmp_file, "rb", source);
    if (file_status != READ_OK) {
        return file_status;
    }

    enum read_status deserializer_status = from_bmp(bmp_file, img);
    if (deserializer_status != READ_OK) {
        fclose(bmp_file);
        return deserializer_status;
    }
    fclose(bmp_file);
    return READ_OK;
}

struct bmp_header* create_header(struct image const* img, struct bmp_header* header) {
    *header = (struct bmp_header){
        .bfType = 19778,
        .bfileSize = 0,
        .bfReserved = 0,
        .bOffBits = 54,
        .biSize = 40,
        .biWidth = img -> width,
        .biHeight = img -> height,
        .biPlanes = 1,
        .biBitCount = sizeof(struct pixel) * 8,
        .biCompression = 0,
        .biSizeImage = 0,
        .biXPelsPerMeter = 2834,
        .biYPelsPerMeter = 2834,
        .biClrUsed = 0,
        .biClrImportant = 0
    };

    return header;

}

enum write_status to_bmp(FILE* out, struct image const* img) {
    struct bmp_header header;
    create_header(img, &header);

    uint8_t padding = calc_padding(header.biWidth, header.biBitCount);
    header.bfileSize = sizeof(struct bmp_header) + img -> width * img -> height * sizeof(struct pixel) + padding * img -> height;
    header.biSizeImage = header.bfileSize - header.bOffBits;

    size_t result = fwrite(&header, sizeof(struct bmp_header), 1, out);
    if (result != 1) {
        return WRITE_ERROR;
    }

    fseek(out, header.bOffBits, SEEK_SET);
    struct pixel* pixel;
    for (size_t i = 0; i < header.biHeight; i++) {
        for (size_t z = 0; z < header.biWidth; z++) {
            pixel = img -> data + header.biWidth * i + z;
            result = fwrite(pixel, sizeof(struct pixel), 1, out);
            if (pixel == NULL || result != 1) {
                return WRITE_ERROR;
            }
        }
        fseek(out, padding, SEEK_CUR);
    }

    return WRITE_OK;
}

enum write_status write_to_bmp(struct image const* img, char* source) {
    FILE* new_bmp_file = fopen(source, "wb");

    enum write_status write_status = to_bmp(new_bmp_file, img);
    if (write_status != WRITE_OK) {
        fclose(new_bmp_file);
        return write_status;
    }

    free(img -> data);
    fclose(new_bmp_file);

    return WRITE_OK;
}

