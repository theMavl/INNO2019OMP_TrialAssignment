#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_operations.h"
#include "fs_operations.h"

int main() {
    image *in_image = malloc(sizeof(image));
    if (load_image(in_image, "../sample_images/valve.PPM") != 0) {
        printf("Error\n");
        return 1;
    }

    image *gray_image = to_gray(in_image);
    write_image(gray_image, "../sample_images/valve_grey.PPM");
    write_image(in_image, "../sample_images/valve_replica.PPM");

    int kernel_1[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int kernel_2[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    image *conv_image_1 = malloc(sizeof(image));
    image *conv_image_2 = malloc(sizeof(image));
    image *cont_image = malloc(sizeof(image));

    convolution(gray_image, kernel_1, kernel_2, conv_image_1, conv_image_2, cont_image);

    write_image(conv_image_1, "../sample_images/valve_conv_1.PPM");
    write_image(conv_image_2, "../sample_images/valve_conv_2.PPM");
    write_image(cont_image, "../sample_images/valve_cont.PPM");

    free(in_image->matrix);
    free(in_image);
    free(gray_image->matrix);
    free(gray_image);
    free(conv_image_1->matrix);
    free(conv_image_1);
    free(conv_image_2->matrix);
    free(conv_image_2);
    free(cont_image->matrix);
    free(cont_image);

    return 0;
}