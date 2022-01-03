#include "inc/bmp.h"
#include <inttypes.h>
#include "inc/utils.h"

struct  __attribute__((packed)) bmp_header{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

static uint32_t set_padding(uint32_t width) {
    return (4 - width * 3 % 4) % 4;
}
static struct bmp_header create_bmp_header(uint32_t width, uint32_t height) {
    return (struct bmp_header) {
            .bfType = 0x4D42,
            .bfileSize = width * height * 3 + set_padding(width) * height + sizeof(struct bmp_header),
            .bfReserved = 0,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = 40,
            .biWidth = width,
            .biHeight = height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = width * height * 3 + set_padding(width) * height,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };
}

static enum close_status close_file( FILE* file){
    if(!file){
        return CLOSE_ERROR_IN_FILE;
    }
    if(fclose(file) != 0){
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}

static bool read_header( FILE* in, struct bmp_header* header){
    return fread(header, sizeof(struct bmp_header), 1, in);
}

void check_header(FILE* in, struct bmp_header* header){
    if(!read_header(in, header)){
        error_in_read_handler(READ_INVALID_HEADER);
    }
}

enum read_status from_bmp( FILE* in, struct image* img ){
    struct bmp_header header = {0};
    check_header(in, &header);
    if(header.bfType != 0x4D42){
        return READ_INVALID_SIGNATURE;
    }
    if(header.biCompression != 0){
        return READ_INVALID_FORMAT;
    }
    *img = create_image(header.biWidth, header.biHeight);
    uint32_t const padding = set_padding(img->width);
    for(uint32_t i = 0; i < header.biHeight; ++i){
        size_t count = fread(&img->data[i*img->width], sizeof(struct pixel), img->width, in);
        if(count != img->width){
            destroy_image(img);
            return READ_INVALID_BITS;
        }
        if (fseek(in, padding, SEEK_CUR) != 0) {
            destroy_image(img);
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}

enum open_status from_file(const char* filename, struct image* img){
    if(!filename){
        error_in_open_handler(OPEN_ERROR);
    }
    FILE* file = fopen(filename, "rb");
    if(!file){
        error_in_open_handler(OPEN_INVALID_FILE);
    }
    enum read_status read_status = from_bmp(file, img);
    if(read_status != READ_OK){
        error_in_read_handler(read_status);
    }
    enum close_status close_status = close_file(file);
    if(close_status != CLOSE_OK){
        error_in_close_handler(close_status);
    }
    return OPEN_OK;
}



static bool write_header( FILE* out, struct bmp_header* header){
    return fwrite(header, sizeof(struct bmp_header), 1, out);
}

enum write_status to_bmp( FILE* out, struct image const* img ){
    if(!out){
        return WRITE_INVALID_FILE;
    }
    struct bmp_header header = create_bmp_header(img->width, img->height);
    if (write_header(out, &header) != 1) {
        return WRITE_INVALID_HEADER;
    }
    uint32_t const padding = set_padding(img->width);
    int32_t padding_value = 0;
    for(uint64_t i = 0; i < header.biHeight; ++i){
        size_t count = fwrite(&img->data[i * img->width], sizeof(struct pixel), img->width, out);
        if(count != img->width){
            return WRITE_INVALID_BITS;
        }
        if(fwrite(&padding_value, 1, padding, out) != padding){
            return WRITE_INVALID_BITS;
        }
    }
    return WRITE_OK;
}

enum open_status to_file(const char* filename, struct image* img){
    if(!filename){
        error_in_open_handler(OPEN_ERROR);
    }
    FILE* file = fopen(filename, "wb");
    if(!file){
        error_in_open_handler(OPEN_INVALID_FILE);
    }
    enum write_status write_st = to_bmp(file, img);
    if( write_st != WRITE_OK){
        error_in_write_handler(write_st);
    }
    enum close_status close_st = close_file(file);
    if(close_st == CLOSE_ERROR){
        error_in_close_handler(close_st);
    }
    return OPEN_OK;
}
