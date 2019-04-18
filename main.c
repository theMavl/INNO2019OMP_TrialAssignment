#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image_operations.h"
#include "fs_operations.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Parameters are needed. Use cont --help\n");
        return 1;
    }

    struct timespec start, finish, total_time_start, total_time_finish;
    double elapsed;

    if (strcmp(argv[1], "--help") == 0) {
        printf("SYNOPSIS\n"
               "\tcont SOURCE DESTINATION [-t threads_n] [--abs] [-i DEST_IMAGE_H DEST_IMAGE_V] [-f FORMAT]\n\n");
        printf("OPTIONS\n\t-t threads_n\n\t\tNumber of threads\n\n"
               "\t--abs\n\t\tUse absolute value for approximating gradient instead of square root\n"
               "\t\t(absolute value is faster but might be less accurate)\n\n"
               "\t-i DEST_IMAGE_H DEST_IMAGE_V\n\t\tSave intermediate images, i.e. the results of horizontal and vertical\n"
               "\t\tconvolutions\n\n"
               "\t-f FORMAT\n\t\tOutput format (P3 and P6 are supported). By default it will save the image in original format.\n"
               "\t\tconvolutions\n");
        return 0;
    }

    MODE = 0;       // Square root
    THREADS_N = 1;  // Single thread
    save_intermediate = 0;
    unsigned char output_format = 0;

    char *filename_in = argv[1];
    char *filename_out = argv[2];

    // Intermediate images (if user wants them to be saved)
    char *filename_conv_h;
    char *filename_conv_v;
    image *conv_image_h;
    image *conv_image_v;

    for (int arg_n = 3; arg_n < argc; arg_n++) {
        if (strcmp(argv[arg_n], "--abs") == 0) {
            // Select contour highlighting mode
            MODE = ABSOLUTE;
        } else if (strcmp(argv[arg_n], "-t") == 0) {
            // Set threads number
            THREADS_N = (int) strtol(argv[arg_n + 1], NULL, 10);
            arg_n += 1;
        } else if (strcmp(argv[arg_n], "-i") == 0) {
            // Save intermediate images
            filename_conv_h = argv[arg_n + 1];
            filename_conv_v = argv[arg_n + 2];
            arg_n += 2;
            save_intermediate = 1;
        } else if (strcmp(argv[arg_n], "-f") == 0) {
            if (strcmp(argv[arg_n + 1], "P6") == 0)
                output_format = P6;
            else if (strcmp(argv[arg_n + 1], "P3") == 0)
                output_format = P3;
            else
                printf("Unknown format %s. Original format will be kept.\n", argv[arg_n + 1]);
            arg_n++;
        } else {
            printf("Unknown parameter \"%s\". Use cont --help\n", argv[arg_n]);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &total_time_start);

    image *in_image = malloc(sizeof(image));

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (load_image(in_image, filename_in) != 0) {
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    if (output_format == 0)
        output_format = in_image->format;

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("load time: %fs\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);
    image *gray_image = malloc(sizeof(image));
    to_gray(in_image, gray_image);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("to_gray time: %fs\n", elapsed);

    if (save_intermediate) {
        conv_image_h = malloc(sizeof(image));
        conv_image_v = malloc(sizeof(image));
    }
    image *cont_image = malloc(sizeof(image));
    cont_image->matrix = malloc(sizeof(char) * in_image->height * in_image->width);

    clock_gettime(CLOCK_MONOTONIC, &start);
    sobel(gray_image, conv_image_h, conv_image_v, cont_image);

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);

    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Sobel time: %fs\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (save_intermediate) {
        conv_image_h->format = output_format;
        conv_image_v->format = output_format;
        write_image(conv_image_h, filename_conv_h);
        write_image(conv_image_v, filename_conv_v);
    }

    cont_image->format = output_format;

    write_image(cont_image, filename_out);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("write time: %fs\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &total_time_finish);
    elapsed = (total_time_finish.tv_sec - total_time_start.tv_sec);
    elapsed += (total_time_finish.tv_nsec - total_time_start.tv_nsec) / 1000000000.0;
    printf("\nTotal time: %fs\n", elapsed);

    free(in_image->matrix);
    free(in_image);
    free(gray_image->matrix);
    free(gray_image);
    if (save_intermediate) {
        free(conv_image_h->matrix);
        free(conv_image_h);
        free(conv_image_v->matrix);
        free(conv_image_v);
    }
    free(cont_image->matrix);
    free(cont_image);
    return 0;
}