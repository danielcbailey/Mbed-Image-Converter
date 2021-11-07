# Mbed-Image-Converter
Convert images to C files for ECE 2035 Project 2-2.

### Usage
You are intended to compile the code yourself on your target platform. It should compile for any platform. Simply download the source code and run the following command from a terminal with access to GCC from the source code's directory: `gcc main.c stb_image.h -o imgconv -lm`.

After you have compiled the code, place the binary in the directory you have your images stored. The software will accept almost any image format you provide, but do not use GIFs, JPEGs with 12-bit channels, or JPEGs with arithmetic coding.

To convert an image, you run the executable as follows: `./imgconv [image file] [output name]`. Example: `./imgconv myImage.png sprite1`.

The output name is the variable name you want the array to have in the C file. It will make the output file name [output name].c

### Notes
This software will convert images into the format expected by the ULCD_4DGL_SE library. Unlike some other online converters, this converter will convert colors correctly. On that note, the ULCD library uses 32-bit unsigned integers to express a single pixel so that standard 24-bit colors can be used with the library. The problem is that the LPC 1768 (your embedded device) only has 64 KB of RAM, which is quite limited so any unnecessary memory is costly. The ULCD_4DGL actually uses 16-bit colors, so half of the memory to store images as 32-bits per pixel is actually wasted. Of note, however, is that this array will be stored in FLASH, not RAM, where memory is less of a concern (there is 512KB), but the ULCD_4DGL library dynamically allocates memory to send the image over to the display in order to convert the array to the format expected by the display.

With that said, it would be smarter to just store the array in the exact format the LCD expects. This is how I have used that LCD previously, and my old code is available on my github, along with the code that I used to generate c arrays from images for that format. Should you want to try to make this optimization, you can easily modify this code to suite your needs, but I will not provide a version of this C code that does exactly that.
