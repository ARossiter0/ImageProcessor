#include "PixelProcessor.h"

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            pArr[h][w].r += rShift;
            pArr[h][w].g += gShift;
            pArr[h][w].b += bShift;
        }
    }
}
