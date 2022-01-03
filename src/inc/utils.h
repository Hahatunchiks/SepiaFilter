
#ifndef ASSIGNMENT_SEPIA_FILTER_UTILS_H
#define ASSIGNMENT_SEPIA_FILTER_UTILS_H

#include "bmp.h"



void error_in_open_handler(enum open_status e);
void error_in_read_handler(enum read_status e);
void error_in_close_handler(enum close_status e);
void error_in_write_handler(enum write_status e);

_Noreturn void err(const char *msg, ...);

#endif //ASSIGNMENT_SEPIA_FILTER_UTILS_H
