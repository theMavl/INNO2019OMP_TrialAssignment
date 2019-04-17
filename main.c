#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image_operations.h"
#include "fs_operations.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "--help") == 0) {
        printf("SYNOPSIS\n"
               "\t\tconv SOURCE DESTINATION [-t threads_n] [--abs] [-i DEST_IMAGE_H DEST_IMAGE_V]\n\n");
        printf("OPTIONS\n\t\t-t threads_n\n\t\t\tNumber of threads\n\n"
               "\t\t--abs\n\t\t\tUse absolute value for approximating gradient instead of square root "
               "(absolute value is faster but might be less accurate)\n\n"
               "\t\t-i DEST_IMAGE_H DEST_IMAGE_V\n\t\t\tSave intermediate images, i.e. the results of horizontal and vertical convolutions\n");
        return 0;
    }

    MODE = 0;       // Square root
    THREADS_N = 1;  // Single thread

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
        }
        else if (strcmp(argv[arg_n], "-t") == 0) {
            // Set threads number
            THREADS_N = (int) strtol(argv[arg_n + 1], NULL, 10);
            arg_n += 1;
        }
        else if (strcmp(argv[arg_n], "-i") == 0) {
            // Save intermediate images
            filename_conv_h = argv[arg_n + 1];
            filename_conv_v = argv[arg_n + 2];
            arg_n += 2;
            save_intermediate = 1;
        } else {
            printf("Unknown parameter \"%s\". Use conv --help\n", argv[arg_n]);
            return 1;
        }
    }

    image *in_image = malloc(sizeof(image));

    clock_t begin = clock();
    clock_t total_time = clock();
    if (load_image(in_image, filename_in) != 0) {
        return 1;
    }
    double time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("load time: %fs\n", time_spent);

    begin = clock();
    image *gray_image = to_gray(in_image);
    time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("to_gray time: %fs\n", time_spent);

    int kernel_1[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int kernel_2[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    if (save_intermediate) {
        conv_image_h = malloc(sizeof(image));
        conv_image_v = malloc(sizeof(image));
    }
    image *cont_image = malloc(sizeof(image));

    begin = clock();
    sobel(gray_image, kernel_1, kernel_2, conv_image_h, conv_image_v, cont_image);
    time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("Sobel time: %fs\n", time_spent);


    begin = clock();
    if (save_intermediate) {
        write_image(conv_image_h, filename_conv_h);
        write_image(conv_image_v, filename_conv_v);
    }
    write_image(cont_image, filename_out);
    time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("write time: %fs\n", time_spent);

    time_spent = (double) (clock() - total_time) / CLOCKS_PER_SEC;
    printf("\nTotal time: %fs\n", time_spent);

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