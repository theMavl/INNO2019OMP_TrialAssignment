//
// Created by mavl on 16.04.19.
//

#ifndef FS_OPERATIONS_H
#define FS_OPERATIONS_H

#include "image_operations.h"

// Formats
#define P2 2
#define P3 3
#define P6 6

int load_image(image *image, const char *filename);

int write_image(image *out_image, const char *filename);

#endif
