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
    unsigned char color_range;
    unsigned char *matrix;
    unsigned char channels;
} image;

typedef struct _convolve_thread_parameters {
    int start;
    int end;
} convolve_thread_parameters;


image *to_gray(image *original_image);

int sobel(image *image_s, int *kernel_1, int *kernel_2, image *conv_image_1, image *conv_image_2,
          image *cont_image_t);

#endif