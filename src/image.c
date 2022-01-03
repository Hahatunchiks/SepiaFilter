#include "inc/image.h"
struct image create_image(uint64_t w, uint64_t h){
    return (struct image) {.width = w, .height = h, .data = malloc(sizeof(struct pixel) * w * h)};
}

void destroy_image(struct image* img){
    free(img->data);
    free(img);
}
