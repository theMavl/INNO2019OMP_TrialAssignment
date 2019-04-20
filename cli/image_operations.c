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

// Converting 2D matrix coordinate to 1D
#define get_matrix_value(_value, _image, _x, _y) do { \
    _value = _image->matrix[(_x)*_image->width+(_y)];\
} while (0);

#define set_matrix_value(_value, _image, _x, _y) do { \
    _image->matrix[(_x)*_image->width+(_y)] = _value;\
} while (0);

// Global variables used in threads
int kernel_h[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int kernel_v[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
image *rgb_image;
image *gray_image;
image *conv_image_h;
image *conv_image_v;
image *cont_image;

/**
 * Convert specified lines of the rgb_image to grayscale and store in gray_image
 * @param start start line index
 * @param end finish line index
 */
void to_gray_line(long start, long end) {
    long rgb_ptr;
    int gray_value = 0;
    for (long i = start; i < end; i++) {
        rgb_ptr = i * rgb_image->channels;
        if (rgb_image->channels == 3) {
            // Nice gray
            gray_image->matrix[i] = (unsigned int) round(
                    0.2989 * rgb_image->matrix[rgb_ptr] + 0.5870 * rgb_image->matrix[rgb_ptr + 1] +
                    0.1140 * rgb_image->matrix[rgb_ptr + 2]);
        } else {
            // Average of all channels
            gray_value = 0;
            for (int j = 0; j < rgb_image->channels; j++) {
                gray_value += rgb_image->matrix[rgb_ptr + i];
            }
            gray_image->matrix[i] = (unsigned char) round(gray_value / (rgb_image->channels * 0.1));
        }
    }
}


/**
 * Wrapper for multi-threaded converting specified rgb_image lines to gray_image lines
 * @param arg start and end line indexes in thread_parameters
 */
void *to_gray_line_wrapper(void *arg) {
    thread_parameters *p = (thread_parameters *) arg;
    to_gray_line(p->start, p->end);
}

/**
 * Convert given image to grayscale
 * @param original_image given image
 * @param gray_image_t destination gray image (has to be allocated)
 */
void to_gray(image *original_image, image *gray_image_t) {
    // Publish global variable
    gray_image = gray_image_t;
    rgb_image = original_image;
    unsigned long matrix_size = original_image->height * original_image->width;
    gray_image->height = original_image->height;
    gray_image->width = original_image->width;
    gray_image->format = P2;
    gray_image->color_range = original_image->color_range;
    gray_image->channels = 1;
    gray_image->matrix = malloc(sizeof(int) * matrix_size);

    for (int i = 0; i < matrix_size; i++)
        gray_image->matrix[i] = 0;

    if (THREADS_N == 1) {
        to_gray_line(0, matrix_size);
    } else {
        long image_division = matrix_size / THREADS_N;

        if (gray_image->height % THREADS_N > 0)
            image_division++;

        pthread_t threads[THREADS_N];
        thread_parameters p[THREADS_N];

        for (int i = 0; i < THREADS_N; i++) {
            p[i].start = image_division * i;
            p[i].end = p[i].start + image_division;
            if (p[i].end > matrix_size) p[i].end = matrix_size;
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_create(&threads[i], NULL, to_gray_line_wrapper, &p[i]);
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

/**
 * Convolve pixel at x,y (using global kernel_1 and kernel_2) and find its gradient based on surrounding pixels
 * @param x given x
 * @param y given y
 */
void process_pixel(long x, long y) {
    int sum_h = 0; // Horizontal convolution
    int sum_v = 0; // Vertical convolution
    int sum_m = 0; // Gradient
    int value = 0; // Temp value

    int *kernel_v_ptr = kernel_v;   // Pointer to convolution kernel_v array
    int *kernel_h_ptr = kernel_h;   // Pointer to convolution kernel_h array
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            get_matrix_value(value, gray_image, x + j, y + i);
            sum_v += value * *kernel_v_ptr;
            sum_h += value * *kernel_h_ptr;
            kernel_v_ptr++;
            kernel_h_ptr++;
        }
    }

    // Trim to boundaries
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

/**
 * Process (convolution and gradient approximation) specified lines of an image
 * @param start start line index
 * @param end finish line index
 */
void process_line(long start, long end) {
    for (long x = start; x < end; x++) {
        for (int y = 1; y < gray_image->width - 1; y++) {
            process_pixel(x, y);
        }
    }
}

/**
 * Wrapper for multi-threaded processing (convolution + gradient approximation) lines of image
 * @param arg start and end line indexes in thread_parameters
 */
void *process_line_wrapper(void *arg) {
    thread_parameters *p = (thread_parameters *) arg;
    process_line(p->start, p->end);
}

/**
 * Generating contour image from given one using Sobel operator
 * @param image_s given original image
 * @param conv_image_1 place where to store intermediate image_h (ignored unless -i flag is set). Has to be allocated.
 * @param conv_image_2 place where to store intermediate image_v (ignored unless -i flag is set). Has to be allocated.
 * @param cont_image_t place where to store contour image. Has to be allocated.
 * @return returns 0 on success, 1 if input image has more than 1 channel.
 */
int sobel(image *image_s, image *conv_image_1, image *conv_image_2, image *cont_image_t) {
    if (image_s->channels != 1) {
        fprintf(stderr, "Can not process_pixel multichannel images\n");
        return 1;
    }

    long matrix_size = gray_image->height * gray_image->width;

    // Publish variables so that threads can see them
    gray_image = image_s;
    cont_image = cont_image_t;

    if (save_intermediate) {
        conv_image_h = conv_image_1;
        conv_image_h->height = gray_image->height;
        conv_image_h->width = gray_image->width;
        conv_image_h->format = gray_image->format;
        conv_image_h->color_range = gray_image->color_range;
        conv_image_h->channels = 1;
        conv_image_h->matrix = malloc(sizeof(int) * matrix_size);

        conv_image_v = conv_image_2;
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
        thread_parameters p[THREADS_N];

        for (int i = 0; i < THREADS_N; i++) {
            p[i].start = image_division * i + 1;
            p[i].end = p[i].start + image_division;
            if (p[i].end >= gray_image->height) p[i].end = gray_image->height - 1;
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_create(&threads[i], NULL, process_line_wrapper, &p[i]);
        }

        for (int i = 0; i < THREADS_N; i++) {
            pthread_join(threads[i], NULL);
        }
    }
    return 0;
}

