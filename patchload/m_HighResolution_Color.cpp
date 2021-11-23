#include "pch.h"
#ifdef MODULES_HIGHRESOLUTION
D2HD::D2HDColor::D2HDColor(const unsigned char red, const unsigned char green,
    const unsigned char blue, const unsigned char tint) : red(red), green(green),
    blue(blue), tint(tint) 
{
}

unsigned int D2HD::D2HDColor::getRGBFormat() const 
{
    unsigned int redRGB = (((unsigned int)red) << (8 * 3)) & 0xFF000000;
    unsigned int greenRGB = ((unsigned int)green << (8 * 2)) & 0x00FF0000;
    unsigned int blueRGB = ((unsigned int)blue << (8 * 1)) & 0x0000FF00;
    unsigned int tintRGB = ((unsigned int)tint) & 0x000000FF;

    return redRGB | greenRGB | blueRGB | tintRGB;
}

unsigned int D2HD::D2HDColor::getBGRFormat() const 
{
    unsigned int redBGR = (((unsigned int)red) << (8 * 1)) & 0x0000FF00;
    unsigned int greenBGR = (((unsigned int)green) << (8 * 2)) & 0x00FF0000;
    unsigned int blueBGR = ((unsigned int)blue << (8 * 3)) & 0xFF000000;
    unsigned int tintBGR = ((unsigned int)tint) & 0x000000FF;

    return redBGR | greenBGR | blueBGR | tintBGR;
}

D2HD::D2HDColor D2HD::D2HDColor::createFromRGBFormat(const unsigned int color) 
{
    unsigned char red = (((unsigned int)color) >> (8 * 3)) & 0xFF;
    unsigned char green = (((unsigned int)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((unsigned int)color) >> (8 * 1)) & 0xFF;
    unsigned char tint = color & 0xFF;

    return D2HD::D2HDColor(red, green, blue, tint);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromRGBFormat(const std::string&
    colorHex) 
{
    const unsigned int colorValue = std::stoul(colorHex, nullptr, 16);
    return createFromRGBFormat(colorValue);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromRGBFormat(const std::wstring&
    colorHex) 
{
    const unsigned int colorValue = std::stoul(colorHex, nullptr, 16);
    return createFromRGBFormat(colorValue);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromBGRFormat(const unsigned int color) 
{
    unsigned char red = (((unsigned int)color) >> (8 * 1)) & 0xFF;
    unsigned char green = (((unsigned int)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((unsigned int)color) >> (8 * 3)) & 0xFF;
    unsigned char tint = ((unsigned int)color) & 0xFF;

    return D2HD::D2HDColor(red, green, blue, tint);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromBGRFormat(const std::string&
    colorHex) {
    const unsigned int colorValue = std::stoul(colorHex, nullptr, 16);
    return createFromBGRFormat(colorValue);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromBGRFormat(const std::wstring&
    colorHex) {
    const unsigned int colorValue = std::stoul(colorHex, nullptr, 16);
    return createFromBGRFormat(colorValue);
}
#endif