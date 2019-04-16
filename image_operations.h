//
// Created by mavl on 16.04.19.
//

#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

typedef struct _image {
    unsigned char format;
    unsigned int width;
    unsigned int height;
    unsigned char color_range;
    unsigned char *matrix;
    unsigned char channels;
} image;


image *to_gray(image *original_image);

#endif