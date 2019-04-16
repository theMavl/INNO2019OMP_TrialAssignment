//
// Created by mavl on 16.04.19.
//
#include <stdlib.h>

#include "image_operations.h"
#include "fs_operations.h"

#include <math.h>

image *to_gray(image *original_image) {
    image *gray_image = malloc(sizeof(image));
    gray_image->height = original_image->height;
    gray_image->width = original_image->width;
    gray_image->format = original_image->format;
    gray_image->color_range = original_image->color_range;
    gray_image->channels = 1;

    long matrix_size = gray_image->height * gray_image->width;

    gray_image->matrix = malloc(sizeof(char) * matrix_size);

    unsigned char *rgb_matrix_ptr = original_image->matrix;
    unsigned char gray_level = 0;

    for (int i = 0; i < matrix_size; i++) {
        gray_level = (unsigned char) round(
                0.2989 * rgb_matrix_ptr[0] + 0.5870 * rgb_matrix_ptr[1] + 0.1140 * rgb_matrix_ptr[2]);
        gray_image->matrix[i] = gray_level;
        rgb_matrix_ptr += 3;
    }

    return gray_image;
}