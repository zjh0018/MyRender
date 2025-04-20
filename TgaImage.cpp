#include <iostream>
#include <cstring>
#include "TgaImage.h"

TgaImage::TgaImage():m_imageData(nullptr), m_byteSize(0), m_imageType(1)
{
    m_head.imageWidth = 0;
    m_head.imageHeight = 0;
    memset((void*)&m_head, 0, sizeof(m_head));
}

TgaImage::TgaImage(int w, int h, int imageType):m_imageData(nullptr), m_byteSize(w * h * imageType), m_imageType(imageType)
{
    m_imageData = new unsigned char[m_byteSize];
    memset(m_imageData, 0, m_byteSize);
    memset((void*)&m_head, 0, sizeof(m_head));
    //setHeader
    m_head.imageType = (m_imageType == GRAY ? 3 : 2);
    m_head.imageWidth = w;
    m_head.imageHeight = h;
    m_head.pixedDepth = imageType << 3;
    m_head.imageDescriptor = 0x20;
}

TgaImage::~TgaImage()
{
    if (m_imageData) {
        delete[] m_imageData;
        m_imageData = nullptr;
    }
}

bool TgaImage::writeTagFile(const char* filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "无法打开文件：" << filename << std::endl;
        outfile.close();
        return false;
    }
    outfile.write((char*)&m_head, sizeof(m_head));
    if (!outfile.good()) {
        std::cerr << "写入文件头失败：" << std::endl;
        outfile.close();
        return false;
    }
    outfile.write((char*)m_imageData, m_byteSize);
    if (!outfile.good()) {
        std::cerr << "写入像素数据失败：" << std::endl;
        outfile.close();
        return false;
    }
    unsigned char developer_area_ref[4] = { 0, 0, 0, 0 };
    unsigned char extension_area_ref[4] = { 0, 0, 0, 0 };
    unsigned char footer[18] = { 'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0' };
    outfile.write((char*)developer_area_ref, sizeof(developer_area_ref));
    if (!outfile.good()) {
        std::cerr << "写入开发者区域失败：" << std::endl;
        outfile.close();
        return false;
    }
    outfile.write((char*)extension_area_ref, sizeof(extension_area_ref));
    if (!outfile.good()) {
        std::cerr << "写入扩展区域失败：" << std::endl;
        outfile.close();
        return false;
    }
    outfile.write((char*)footer, sizeof(footer));
    if (!outfile.good()) {
        std::cerr << "写入文件脚注失败：" << std::endl;
        outfile.close();
        return false;
    }
    outfile.close();
    return true;
}

bool TgaImage::readTagFile()
{
    return false;
}

bool TgaImage::set(int x, int y, TGA_Color color)
{
    if (!m_imageData || x < 0 || y < 0 || x >= m_head.imageWidth || y >= m_head.imageHeight) {
        return false;
    }
    memcpy(m_imageData + (x + y * m_head.imageHeight) * m_imageType, color.raw, m_imageType);
    return true;
}

