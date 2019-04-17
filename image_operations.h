//
// Created by mavl on 16.04.19.
//

#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#define THREADS 4

typedef struct _image {
    unsigned char format;
    unsigned int width;
    unsigned int height;
    unsigned char color_range;
    unsigned char *matrix;
    unsigned char channels;
} image;

struct convolve_thread_parameters {
    int start;
    int end;
};


image *to_gray(image *original_image);

int sobel(image *image_s, int *kernel_1, int *kernel_2, image *conv_image_1, image *conv_image_2,
          image *cont_image_t);

#endif