#include "BmpProcessor.h"
#include <stdlib.h>
#include <string.h>


void readBMPHeader(FILE* file, struct BMP_Header* header) {
    fread(&header->signature, sizeof(char)*2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserved1, sizeof(short), 1, file);
    fread(&header->reserved2, sizeof(short), 1, file);
    fread(&header->offset_pixel_array, sizeof(int), 1, file);
}

void writeBMPHeader(FILE* file, struct BMP_Header* header) {
    fwrite(&header->signature, sizeof(char)*2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offset_pixel_array, sizeof(int), 1, file);
}

void readDIBHeader(FILE* file, struct DIB_Header* header) {
    fread(&header->header_size, sizeof(int), 1, file);
    fread(&header->width, sizeof(int), 1, file);
    fread(&header->height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->bits_per_pixel, sizeof(short), 1, file);
    fread(&header->compression, sizeof(int), 1, file);
    fread(&header->image_size, sizeof(int), 1, file);
    fread(&header->x_pxl_per_meter, sizeof(int), 1, file);
    fread(&header->y_pxl_per_meter, sizeof(int), 1, file);
    fread(&header->colors_in_table, sizeof(int), 1, file);
    fread(&header->imp_color_count, sizeof(int), 1, file);
}

void writeDIBHeader(FILE* file, struct DIB_Header* header) {
    fwrite(&header->header_size, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->bits_per_pixel, sizeof(short), 1, file);
    fwrite(&header->compression, sizeof(int), 1, file);
    fwrite(&header->image_size, sizeof(int), 1, file);
    fwrite(&header->x_pxl_per_meter, sizeof(int), 1, file);
    fwrite(&header->y_pxl_per_meter, sizeof(int), 1, file);
    fwrite(&header->colors_in_table, sizeof(int), 1, file);
    fwrite(&header->imp_color_count, sizeof(int), 1, file);
}

void makeBMPHeader(struct BMP_Header* header, int width, int height) {
    strcpy(header->signature, "BM");
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offset_pixel_array = 54;
    int width_bytes = (width * 3) + (4 - (width * 3) % 4);
    header->size = width_bytes * height + header->offset_pixel_array;
}

void makeDIBHeader(struct DIB_Header* header, int width, int height) {
    header->header_size = 40;
    header->width = width;
    header->height = height;
    header->planes = 1;
    header->bits_per_pixel = 24;
    header->compression = 0;
    header->image_size = ((width * 3) + (4 - (width * 3) % 4)) * height;
    header->x_pxl_per_meter = 3780;
    header->y_pxl_per_meter = 3780;
    header->colors_in_table = 0;
    header->imp_color_count = 0;
}


void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {
    int padding = 4 - ((width * 3) % 4);
    if (padding == 4) padding = 0;
    for (int h = height - 1; h > 0; h--) {
        for (int w = 0; w < width; w++) {
            fread(&pArr[h][w].b, sizeof(unsigned char), 1, file);
            fread(&pArr[h][w].g, sizeof(unsigned char), 1, file);
            fread(&pArr[h][w].r, sizeof(unsigned char), 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }
}

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) { 
    int padding = 4 - ((width * 3) % 4);
    if (padding == 4) padding = 0;
    int pad = 0;
    for (int h = height - 1; h > 0; h--) {
        for (int w = 0; w < width; w++) {
            fwrite(&pArr[h][w].b, sizeof(unsigned char), 1, file);
            fwrite(&pArr[h][w].g, sizeof(unsigned char), 1, file);
            fwrite(&pArr[h][w].r, sizeof(unsigned char), 1, file);
        }
        fwrite(&pad, sizeof(unsigned char), padding, file);
    }
}