#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image_operations.h"
#include "fs_operations.h"

int main(int argc, char *argv[]) {
    // TODO: Save convolution images param
    char *filename_in = argv[1];
    char *filename_out = argv[2];

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

    //write_image(gray_image, "../sample_images/pilot_grey.PPM");
    //write_image(in_image, "../sample_images/pilot_replica.PPM");

    int kernel_1[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int kernel_2[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    image *conv_image_1;// = malloc(sizeof(image));
    image *conv_image_2;// = malloc(sizeof(image));
    image *cont_image = malloc(sizeof(image));

    begin = clock();
    sobel(gray_image, kernel_1, kernel_2, conv_image_1, conv_image_2, cont_image);
    time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("Sobel time: %fs\n", time_spent);

    //write_image(conv_image_1, "../sample_images/pilot_conv_1.PPM");
    //write_image(conv_image_2, "../sample_images/pilot_conv_2.PPM");
    begin = clock();
    write_image(cont_image, filename_out);
    time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("write time: %fs\n", time_spent);

    time_spent = (double) (clock() - total_time) / CLOCKS_PER_SEC;
    printf("\nTotal time: %fs\n", time_spent);

    free(in_image->matrix);
    free(in_image);
    free(gray_image->matrix);
    free(gray_image);
//    free(conv_image_1->matrix);
//    free(conv_image_1);
//    free(conv_image_2->matrix);
//    free(conv_image_2);
    free(cont_image->matrix);
    free(cont_image);

    return 0;
}