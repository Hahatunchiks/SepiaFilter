#include "inc/sepia-impl.h"

static const float byte_to_float[256] = {
        0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f,
        32.0f, 33.0f, 34.0f, 35.0f, 36.0f, 37.0f, 38.0f, 39.0f, 40.0f, 41.0f, 42.0f, 43.0f, 44.0f, 45.0f, 46.0f, 47.0f,
        48.0f, 49.0f, 50.0f, 51.0f, 52.0f, 53.0f, 54.0f, 55.0f, 56.0f, 57.0f, 58.0f, 59.0f, 60.0f, 61.0f, 62.0f, 63.0f,
        64.0f, 65.0f, 66.0f, 67.0f, 68.0f, 69.0f, 70.0f, 71.0f, 72.0f, 73.0f, 74.0f, 75.0f, 76.0f, 77.0f, 78.0f, 79.0f,
        80.0f, 81.0f, 82.0f, 83.0f, 84.0f, 85.0f, 86.0f, 87.0f, 88.0f, 89.0f, 90.0f, 91.0f, 92.0f, 93.0f, 94.0f, 95.0f,
        96.0f, 97.0f, 98.0f, 99.0f, 100.0f, 101.0f, 102.0f, 103.0f, 104.0f, 105.0f, 106.0f, 107.0f, 108.0f, 109.0f,
        110.0f, 111.0f,
        112.0f, 113.0f, 114.0f, 115.0f, 116.0f, 117.0f, 118.0f, 119.0f, 120.0f, 121.0f, 122.0f, 123.0f, 124.0f, 125.0f,
        126.0f, 127.0f,
        128.0f, 129.0f, 130.0f, 131.0f, 132.0f, 133.0f, 134.0f, 135.0f, 136.0f, 137.0f, 138.0f, 139.0f, 140.0f, 141.0f,
        142.0f, 143.0f,
        144.0f, 145.0f, 146.0f, 147.0f, 148.0f, 149.0f, 150.0f, 151.0f, 152.0f, 153.0f, 154.0f, 155.0f, 156.0f, 157.0f,
        158.0f, 159.0f,
        160.0f, 161.0f, 162.0f, 163.0f, 164.0f, 165.0f, 166.0f, 167.0f, 168.0f, 169.0f, 170.0f, 171.0f, 172.0f, 173.0f,
        174.0f, 175.0f,
        176.0f, 177.0f, 178.0f, 179.0f, 180.0f, 181.0f, 182.0f, 183.0f, 184.0f, 185.0f, 186.0f, 187.0f, 188.0f, 189.0f,
        190.0f, 191.0f,
        192.0f, 193.0f, 194.0f, 195.0f, 196.0f, 197.0f, 198.0f, 199.0f, 200.0f, 201.0f, 202.0f, 203.0f, 204.0f, 205.0f,
        206.0f, 207.0f,
        208.0f, 209.0f, 210.0f, 211.0f, 212.0f, 213.0f, 214.0f, 215.0f, 216.0f, 217.0f, 218.0f, 219.0f, 220.0f, 221.0f,
        222.0f, 223.0f,
        224.0f, 225.0f, 226.0f, 227.0f, 228.0f, 229.0f, 230.0f, 231.0f, 232.0f, 233.0f, 234.0f, 235.0f, 236.0f, 237.0f,
        238.0f, 239.0f,
        240.0f, 241.0f, 242.0f, 243.0f, 244.0f, 245.0f, 246.0f, 247.0f, 248.0f, 249.0f, 250.0f, 251.0f, 252.0f, 253.0f,
        254.0f, 255.0f
};


static unsigned char sat(uint64_t x) {
    if (x < 256) return x;
    return 255;
}

static void sepia_one(struct pixel *const pixel) {
    static const float c[3][3] = {
            {.393f, .769f, .189f},
            {.349f, .686f, .168f},
            {.272f, .543f, .131f}
    };

    struct pixel const old = *pixel;

    pixel->r = sat(
            byte_to_float[old.r] * c[0][0] + byte_to_float[old.g] * c[0][1] + byte_to_float[old.b] * c[0][2]
    );

    pixel->g = sat(
            byte_to_float[old.r] * c[1][0] + byte_to_float[old.g] * c[1][1] + byte_to_float[old.b] * c[1][2]
    );

    pixel->b = sat(
            byte_to_float[old.r] * c[2][0] + byte_to_float[old.g] * c[2][1] + byte_to_float[old.b] * c[2][2]
    );

}

struct image sepia_c_impl(struct image source) {
    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j++) {
            sepia_one(&source.data[i * source.width + j]);
        }
    }
    return source;
}

//assembly

static void fill_the_buff(const struct pixel *p, float buff[12]) {
    for (size_t i = 0; i < 4; i++) {
        buff[i] = byte_to_float[p->r];
        buff[i + 4] = byte_to_float[p->g];
        buff[i + 8] = byte_to_float[p->b];
    }
}

static void fill_the_pixel(struct pixel *const p, const float buff[12]) {
    p->r = sat(buff[0]);
    p->g = sat(buff[1]);
    p->b = sat(buff[2]);
}

extern void sepia_asm(float buff[12]);

static void sepia_one_asm(struct pixel *const p) {
    float buff[12];
    fill_the_buff(p, buff);
    sepia_asm(buff);
    fill_the_pixel(p, buff);
}

struct image sepia_asm_impl(struct image source) {

    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j+=4) {
            sepia_one_asm(&source.data[i * source.width + j + 0]);
            sepia_one_asm(&source.data[i * source.width + j + 1]);
            sepia_one_asm(&source.data[i * source.width + j + 2]);
            sepia_one_asm(&source.data[i * source.width + j + 3]);
        }
    }
    return source;
}