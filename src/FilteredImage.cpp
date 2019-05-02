#include "FilteredImage.h"
using namespace Gdiplus;

FilteredImage::FilteredImage(const wchar_t* filename): gpBitmap (filename)
{
    //Bitmap gpBitmap (L"test22.bmp");//ctor

       w = gpBitmap.GetWidth();
       h = gpBitmap.GetHeight();
}

unsigned int FilteredImage::GetPixelValue (int x, int y)
{
    Color pixelcolor;

    gpBitmap.GetPixel(x, y, &pixelcolor);
    return (pixelcolor.GetRed() + pixelcolor.GetGreen() + pixelcolor.GetBlue())/3;


}

unsigned int FilteredImage::GetPixelValue (int x, int y, int brightness)
{

    unsigned int a = GetPixelValue(x, y);
    a += brightness;
    if (a > 255)
    {
        return 255;
    }

    return a;


}

//void FilteredImage::GetPixelValue
