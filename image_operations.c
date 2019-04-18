//
// Created by mavl on 16.04.19.
//
#include <stdlib.h>

#include "image_operations.h"
#include "fs_operations.h"

#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define get_matrix_value(_value, _image, _x, _y) do { \
    _value = _image->matrix[(_x)*_image->width+(_y)];\
} while (0);

#define set_matrix_value(_value, _image, _x, _y) do { \
    _image->matrix[(_x)*_image->width+(_y)] = _value;\
} while (0);

// Global variables for threads
int kernel_h[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int kernel_v[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
image *gray_image;
image *conv_image_h;
image *conv_image_v;
image *cont_image;

image *to_gray(image *original_image) {
    unsigned long matrix_size = original_image->height * original_image->width;
    image *gray_image = malloc(sizeof(image));
    gray_image->height = original_image->height;
    gray_image->width = original_image->width;
    gray_image->format = P2;
    gray_image->color_range = original_image->color_range;
    gray_image->channels = 1;
    gray_image->matrix = malloc(sizeof(int) * matrix_size);
    for (int i =0; i < matrix_size; i++)
        gray_image->matrix[i] = 0;

    unsigned int *rgb_ptr = original_image->matrix;

    for (int i = 0; i < matrix_size; i++) {
        gray_image->matrix[i] = (unsigned int) round(
                0.2989 * rgb_ptr[0] + 0.5870 * rgb_ptr[1] + 0.1140 * rgb_ptr[2]);
        // gray_image->matrix[i] = (unsigned char) round((rgb_ptr[0] + rgb_ptr[1] + rgb_ptr[2]) / 3.0);
        rgb_ptr += 3;
    }

    return gray_image;
}

void process_pixel(int x, int y) {
    int sum_h = 0;
    int sum_v = 0;
    int sum_m = 0;
    int value = 0;

    int *kernel_v_ptr = kernel_v;
    int *kernel_h_ptr = kernel_h;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            get_matrix_value(value, gray_image, x + j, y + i);
            sum_v += value * *kernel_v_ptr;
            sum_h += value * *kernel_h_ptr;
            kernel_v_ptr++;
            kernel_h_ptr++;
        }
    }

    if (sum_h < 0) sum_h *= -1;
    if (sum_v < 0) sum_v *= -1;
    if (sum_h > gray_image->color_range) sum_h = gray_image->color_range;
    if (sum_v > gray_image->color_range) sum_v = gray_image->color_range;

    if (MODE == SQROOT)
        sum_m = (int) round(sqrt(sum_h * sum_h + sum_v * sum_v));
    else if (MODE == ABSOLUTE)
        sum_m = abs(sum_h) + abs(sum_v);
    if (sum_m > gray_image->color_range) sum_m = gray_image->color_range;

    if (save_intermediate) {
        set_matrix_value(sum_h, conv_image_h, x, y)
        set_matrix_value(sum_v, conv_image_v, x, y)
    }
    set_matrix_value(sum_m, cont_image, x, y)
}

void process_line(int start, int end) {
    for (int x = start; x < end; x++) {
        for (int y = 1; y < gray_image->width - 1; y++) {
            process_pixel(x, y);
        }
    }
}

void *process_line_wrapper(void *arg) {
    convolve_thread_parameters *p = (convolve_thread_parameters *) arg;
    process_line(p->start, p->end);
}

int sobel(image *image_s, image *conv_image_1, image *conv_image_2, image *cont_image_t) {
    if (image_s->channels != 1) {
        fprintf(stderr, "Can not process_pixel multichannel images\n");
        return 1;
    }

    // Publish variables so that threads can see them
    gray_image = image_s;
    cont_image = cont_image_t;

    long matrix_size = gray_image->height * gray_image->width;

    if (save_intermediate) {
        conv_image_h = conv_image_1;
        conv_image_v = conv_image_2;
        conv_image_h->height = gray_image->height;
        conv_image_h->width = gray_image->width;
        conv_image_h->format = gray_image->format;
        conv_image_h->color_range = gray_image->color_range;
        conv_image_h->channels = 1;
        conv_image_h->matrix = malloc(sizeof(int) * matrix_size);

        conv_image_v->height = gray_image->height;
        conv_image_v->width = gray_image->width;
        conv_image_v->format = gray_image->format;
        conv_image_v->color_range = gray_image->color_range;
        conv_image_v->channels = 1;
        conv_image_v->matrix = malloc(sizeof(int) * matrix_size);
    }

    cont_image->height = gray_image->height;
    cont_image->width = gray_image->width;
    cont_image->format = gray_image->format;
    cont_image->color_range = gray_image->color_range;
    cont_image->channels = 1;
    cont_image->matrix = malloc(sizeof(int) * matrix_size);
    memset(cont_image->matrix, 0, sizeof(char) * matrix_size);

    if (THREADS_N == 1) {
        process_line(1, gray_image->height - 1);
    } else {

        int image_division = gray_image->height / THREADS_N;
        if (gray_image->height % THREADS_N > 0)
            image_division++;

        pthread_t threads[THREADS_N];

        convolve_thread_parameters *p = malloc(sizeof(convolve_thread_parameters *) * THREADS_N);

        // Allocating structures before starting threads gives boost in performance
        for (int i = 0; i < THREADS_N; i++) {
            p[i] = *(convolve_thread_parameters *) malloc(sizeof(convolve_thread_parameters));
            p[i].start = image_division * i + 1;
            p[i].end = p[i].start + image_division;
            if (p[i].end >= gray_image->height) p[i].end = gray_image->height - 2;
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_create(&threads[i], NULL, process_line_wrapper, &p[i]);
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_join(threads[i], NULL);
        }

        free(p);
    }
    return 0;
}

