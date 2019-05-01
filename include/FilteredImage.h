#ifndef FILTEREDIMAGE_H
#define FILTEREDIMAGE_H
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#include <stdio.h>
#include <iostream>


class FilteredImage
{
    public:
        FilteredImage(const wchar_t* filename);
        Bitmap gpBitmap;
        int w, h;
        unsigned int GetPixelValue (int x, int y);

    protected:
        //Color pixelcolor;

    private:
};

#endif // FILTEREDIMAGE_H
