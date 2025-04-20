#pragma once
#include "TgaImage.h"

TGA_Color white = { 255, 255, 255, 255 };
TGA_Color green = { 0, 255, 0, 255 };
TGA_Color red = { 255, 0, 0, 255 };
TGA_Color blue = { 0, 0, 255, 255 };


int main(int argc, char** argv) {
    int width = 64;
    int height = 64;
    TgaImage framebuffer(width, height, TgaImage::RGB);

    int ax = 54, ay = 3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, red);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    framebuffer.writeTagFile("framebuffer.tga");
    return 0;
}