//
// Created by mavl on 16.04.19.
//
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_operations.h"
#include "fs_operations.h"

int load_image(image *image, const char *filename) {
    image->width = 0;
    image->height = 0;
    image->color_range = 0;
    char comment_block = 0;
    char header_is_done = 0;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: failed to open '%s'", filename);
        return 1;
    }

    int c;

    // Parse header
    c = getc(file);
    if (c != 'P') {
        fprintf(stderr, "Error: failed to parse PPM");
        return 1;
    }

    c = getc(file);

    if (c == '3') {
        image->format = P3;
        image->format = P3;
        image->channels = 3;
    } else if (c == '6') {
        image->format = P6;
        image->channels = 3;
    } else {
        fprintf(stderr, "Error: Unsupported format");
        return 1;
    }

    // Read dimensions
    char found = 0;
    char buff[8] = {0};
    int buff_ptr = 0;

    char **end = malloc(sizeof(char));
    while (1) {
        c = getc(file);
        if (c == '#') {
            comment_block = 1;
            continue;
        }
        if (c == '\n' && comment_block) {
            comment_block = 0;
            continue;
        }
        if (comment_block)
            continue;
        if (c == ' ' || c == '\n') {
            if (found) {
                if (image->width == 0) {
                    image->width = (unsigned int) strtol(buff, end, 10);
                } else if (image->height == 0) {
                    image->height = (unsigned int) strtol(buff, end, 10);
                } else if (image->color_range == 0) {
                    image->color_range = (unsigned int) strtol(buff, end, 10);
                    if (image->color_range > 65535) {
                        fprintf(stderr, "Error: Unsupported format (color range is too big)\n");
                        return 1;
                    }
                    break;
                }
                memset(buff, 0, 8);
                buff_ptr = 0;
            }
        } else {
            found = 1;
            buff[buff_ptr] = (char) c;
            buff_ptr++;
        }
    }
    free(end);
    long matrix_size = image->height * image->width * 3;
    image->matrix = malloc(sizeof(int) * matrix_size);

    if (image->format == P6) {
        // Read pixel data

        // In case of 2-byte color range
        char extendent_byte = 0;
        unsigned int tmp_value;
        if (image->color_range > 255)
            extendent_byte = 1;

        for (int i = 0; i < matrix_size; i++) {
            c = getc(file);

            // Skip remaining comments that are after the header
            if (!header_is_done && c == '#') {
                do {
                    c = getc(file);
                } while (c != '\n');
            }
            header_is_done = 1;

            if (c == EOF) {
                fprintf(stderr, "Unexpected End of File\n");
                return 2;
            }

            if (c == ' ' || c == '\n') {
                continue;
            } else {
                if (extendent_byte) {
                    // Put 2 subsequent bytes into one matrix cell
                    tmp_value = (unsigned int) c;
                    tmp_value = tmp_value << sizeof(char) * 8;
                    tmp_value += c;
                    image->matrix[i] = tmp_value;
                } else
                    image->matrix[i] = (unsigned int) c;
            }
        }
    } else if (image->format == P3) {
        buff_ptr = 0;
        found = 0;
        memset(buff, 0, 8);
        int matrix_ptr = 0;

        while (matrix_ptr < matrix_size) {
            c = getc(file);

            // Skip remaining comments that are after the header
            if (!header_is_done && c == '#') {
                do {
                    c = getc(file);
                } while (c != '\n');
            }
            header_is_done = 1;

            if (c == ' ' || c == '\n') {
                if (found) {
                    image->matrix[matrix_ptr] = (unsigned int) strtol(buff, end, 10);
                    memset(buff, 0, 8);
                    buff_ptr = 0;
                    found = 0;
                    matrix_ptr++;
                }
            } else {
                found = 1;
                buff[buff_ptr] = (char) c;
                buff_ptr++;
            }
        }

    }
    return 0;
}

int write_image(image *out_image, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "I/O error\n");
        return 2;
    }
    fprintf(file, "P%d\n%d %d\n%d\n", out_image->format, out_image->width, out_image->height,
            out_image->color_range);
    int real_outputs = 0;
    switch (out_image->format) {
        case P3:
            for (int i = 0; i < out_image->width * out_image->height * out_image->channels; i++) {
                for (int j = out_image->channels; j <= 3; j++) {
                    fprintf(file, "%d ", out_image->matrix[i]);
                    real_outputs += abs(out_image->channels - 3) + 1;
                }
                if (real_outputs % out_image->channels == 0) {
                    if (real_outputs * out_image->channels % out_image->width == 0)
                        fprintf(file, "\n");
                    else
                        fprintf(file, "\t");
                }
            }
            break;
        case P6:
            if (out_image->color_range <= 255) {
                for (int i = 0; i < out_image->width * out_image->height * out_image->channels; i++) {
                    for (int j = out_image->channels; j <= 3; j++) {
                        fprintf(file, "%c", out_image->matrix[i]);
                    }
                }
            } else {
                // 2-byte color range
                unsigned char g[2];
                for (int i = 0; i < out_image->width * out_image->height * out_image->channels; i++) {
                    for (int j = out_image->channels; j <= 3; j++) {
                        g[0] = out_image->matrix[i] >> 8;
                        g[1] = (unsigned char) out_image->matrix[i];
                        fprintf(file, "%c%c", g[0], g[1]);
                    }
                }
            }
            break;
        default:
            fprintf(stderr, "Unsupported format\n");
            return 1;
    }

    fclose(file);
    return 0;
}
