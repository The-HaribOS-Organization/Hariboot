#include <stdint.h>


int kernel_main(void) {//int valeur) {// *framebuffer, uint32_t ppsl) {

    /*for (uint32_t x = 52; x < 400; x++) {
        for (uint32_t y = 60; y < 250; y++) {

            *((uint32_t *)(framebuffer + (4 * pitch * y) + (4 * x))) = 0xFF00FF;
        }
    }*/

    return 55;
}

// gcc -ffreestanding -fno-pic -fno-pie -mno-red-zone -nostdlib -static -Wl,-T loaderScript.ld -o kernel.bin loader.c