#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *bg_subtract(unsigned char *bg_img, unsigned char *fg_img, unsigned char *new_bg_img, int width, int height, int channel, int threshold)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int diff = 0;
            for (int k = 0; k < channel; k++)
            {
                diff += abs(bg_img[i * width * channel + j * channel + k] - fg_img[i * width * channel + j * channel + k]) < threshold ? 1 : 0;
            }
            if(diff != 3) {
                for (int k = 0; k < channel; k++)
                {
                    new_bg_img[i * width * channel + j * channel + k] = fg_img[i * width * channel + j * channel + k];
                }
            }
        }
    }
    return new_bg_img;
}

int main()
{
    // declare variables
    int width, height, channel;
    int threshold = 79;
    char path_bg_img[] = "./images1/background.jpg";
    char path_new_bg_img[] = "./images1/new_background.jpg";
    char path_fg_img[] = "./images1/foreground.jpg";
    char save_path[] = "./images1/new.jpg";

    // read image data
    unsigned char *bg_img = stbi_load(path_bg_img, &width, &height, &channel, 0);
    unsigned char *new_bg_img = stbi_load(path_new_bg_img, &width, &height, &channel, 0);
    unsigned char *fg_img = stbi_load(path_fg_img, &width, &height, &channel, 0);
    

    unsigned char *res_img = bg_subtract(bg_img, fg_img, new_bg_img, width, height, channel, threshold);
    stbi_write_jpg(save_path, width, height, channel, res_img, width * channel);
    printf("New image saved to %s\n", save_path);
}