#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_operations.h"
#include "fs_operations.h"

int main() {
    image *in_image = malloc(sizeof(image));
    if (load_image(in_image, "../sample_images/pop.PPM") != 0) {
        printf("Error\n");
        return 1;
    }

    image *gray_image = to_gray(in_image);
    write_image(in_image, "../sample_images/pop_grey.PPM");

    return 0;
}