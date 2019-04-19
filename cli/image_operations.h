//
// Created by mavl on 16.04.19.
//

#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#define SQROOT 0
#define ABSOLUTE 1

char MODE; // 0 = sqrt, 1 = abs
int THREADS_N;
char save_intermediate; // Define whether should a program store in memory intermediate images

typedef struct _image {
    unsigned char format;
    unsigned int width;
    unsigned int height;
    unsigned int color_range;
    unsigned char channels;
    unsigned int *matrix;
} image;

typedef struct _thread_parameters {
    long start;
    long end;
} thread_parameters;


void to_gray(image *original_image, image* gray_image_t);

int sobel(image *image_s, image *conv_image_1, image *conv_image_2, image *cont_image_t);

#endif