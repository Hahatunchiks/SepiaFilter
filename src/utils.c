#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "inc/utils.h"

static const char* const read_errors_messages[] = {
        [READ_INVALID_SIGNATURE] = "invalid signature in reading",
        [READ_INVALID_BITS] = "invalid bits in reading",
        [READ_INVALID_HEADER] = "error in reading header",
        [READ_INVALID_FORMAT] = "error in  padding",
        [READ_INVALID_CLOSE] = "error in close"
};

static const char* const write_errors_messages[] = {
        [WRITE_ERROR] = "error in writing to file",
        [WRITE_INVALID_HEADER] = "error in writing header",
        [WRITE_INVALID_BITS] = "invalid bits in file",
        [WRITE_INVALID_FILE] = "invalid file",
};

static const char* const open_errors_messages[] = {
        [OPEN_ERROR] = "error in opening file",
        [OPEN_INVALID_FILE] = "error in file"
};

static const char* const close_errors_messages[] = {
        [CLOSE_ERROR] = "error in closing file",
        [CLOSE_ERROR_IN_FILE] = "error in file"
};
_Noreturn void err(const char *msg, ...) {
    va_list args;
    va_start (args, msg);
    vfprintf(stderr, msg, args);
    va_end (args);
    exit(1);
}

void error_in_open_handler(enum open_status e){
    err(open_errors_messages[e]);
}

void error_in_read_handler(enum read_status e){
    err(read_errors_messages[e]);
}

void error_in_close_handler(enum close_status e){
    err(close_errors_messages[e]);
}

void error_in_write_handler(enum write_status e){
    err(write_errors_messages[e]);
}
