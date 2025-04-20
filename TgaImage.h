#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push,1)
struct TGA_Header
{
    char  idLength;
    char  colorMapType;
    char  imageType;
    short firstEntryIndex;
    short colorMapLength;
    char  colorMapEntrySize;
    short xOrigin;
    short yOrigin;
    short imageWidth;
    short imageHeight;
    char  pixedDepth;
    char  imageDescriptor;
};
#pragma pack(pop)

struct TGA_Color
{
    union {
        struct {
            unsigned char b, g, r, a;
        };
        unsigned char raw[4];
        unsigned int val;
    };
    int bytespp;//每个像素的字节数1，3，4
    TGA_Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) :r(R), g(G), b(B), a(A), bytespp(4){}
    TGA_Color(const TGA_Color& color):val(color.val), bytespp(color.bytespp) {
        for (int i = 0; i < 4; i++) {
            raw[i] = color.raw[i];
        }
    }
    TGA_Color& operator=(const TGA_Color& color) {
        if (this == &color) return *this;
        for (int i = 0; i < 4; i++) {
            raw[i] = color.raw[i];
        }
        val = color.val;
        bytespp = color.bytespp;
        return *this;
    }
};

class TgaImage {
private:
    TGA_Header m_head;
    unsigned char* m_imageData;
    unsigned long m_byteSize;
    int m_imageType;
public:
    enum {
        GRAY = 1,
        RGB = 3,
        RGBA = 4
    };
    TgaImage();
    TgaImage(int w, int h, int imageType);
    ~TgaImage();
    bool writeTagFile(const char* filename);
    bool readTagFile();
    bool set(int x, int y, TGA_Color color);
};