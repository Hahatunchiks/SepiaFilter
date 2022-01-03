#ifndef ASSIGNMENT_SEPIA_FILTER_BMP_H
#define ASSIGNMENT_SEPIA_FILTER_BMP_H

#include "image.h"
#include "stdbool.h"

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_FORMAT,
    READ_INVALID_CLOSE
};

enum read_status from_bmp( FILE* in, struct image* img );

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_INVALID_FILE,
    WRITE_INVALID_HEADER,
    WRITE_INVALID_BITS
};
enum write_status to_bmp( FILE* out, struct image const* img );


enum open_status {
    OPEN_OK = 0,
    OPEN_INVALID_FILE,
    OPEN_ERROR
};
enum open_status from_file(const char* filename, struct image* img);
enum open_status to_file(const char* filename, struct image* img);

enum close_status{
    CLOSE_OK = 0,
    CLOSE_ERROR,
    CLOSE_ERROR_IN_FILE
};

#endif //ASSIGNMENT_SEPIA_FILTER_BMP_H
