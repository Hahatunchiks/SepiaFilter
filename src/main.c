#include "inc/utils.h"
#include "inc/sepia-impl.h"
void usage() {
    fprintf(stderr, "Usage: ./main SRC_IMG SRC_OUT PARAM\n");
    fprintf(stderr, "SRC_IMG - full filepath\n");
    fprintf(stderr, "SRC_OUT - result image");
    fprintf(stderr, "PARAM 0 - C implementation, 1 - assembly implementation\n");
}

int main(int argc, char** argv){
    if (argc != 4) usage();
    if (argc < 4) err("Not enough arguments \n");
    if (argc > 4) err("Too many arguments \n");
    struct image orig = {0};
    from_file(argv[1], &orig);
    struct image copy = {0};
    if(*argv[3] == '0' ) {
        copy = sepia_c_impl(orig);
    } else if(*argv[3] == '1'){
        copy = sepia_asm_impl(orig);
    } else {
        err("Bad param value\n");
    }
    to_file(argv[2], &copy);
    return 0;
}
