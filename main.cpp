#if defined(WIN32_LEAN_AND_MEAN)
#undef WIN32_LEAN_AND_MEAN
#endif

#include "FilteredImage.h"

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

int main()
{
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   const wchar_t* filenameR = L"images/red.jpg";
   const wchar_t* filenameG = L"images/green.jpg";
   const wchar_t* filenameB = L"images/blue.jpg";


   FilteredImage Red(filenameR);
   FilteredImage Green(filenameG);
   FilteredImage Blue(filenameB);

   bool resolution = Red.w == Green.w &&
                      Blue.w == Green.w &&
                      Red.w == Blue.w &&
                      Red.h == Green.h &&
                      Blue.h == Green.h &&
                      Red.h == Blue.h;
   if (!resolution)

   {
       std::cout << "The images must be of the same resolution " << std::endl;
       system ("pause");
       return 1;
   }
   //wchar_t* filename = L"images/red.jpg";

   Bitmap mergedBitmap (Red.w, Red.h);
   //BitmapData bitmapData;


   std::cout << "Width is: " << Red.w << std::endl;
   std::cout << "Height is: " << Red.h << std::endl;


   Color gdipColor(255, 0, 0, 255);


int progress = 0;
std::cout << "\r\nMerging images... " << progress << "% done. ";

const unsigned int bitmapSize = Red.w * Red.h;

for (int i = 0; i < Red.w; i++)
   {

       for (int k = 0; k < Red.h; k++)
       {
           int temp_prog = (i * k)*100/bitmapSize;
           //std::cout << "\r" << temp_prog << "% done. ";
           if (temp_prog > progress)
           {
               progress = temp_prog;
               std::cout << "\rMerging images... " << progress << "% done. ";
           }


            int r = Red.GetPixelValue(i,k);
            int g = Green.GetPixelValue(i,k);
            int b = Blue.GetPixelValue(i,k);


/*
            //color correction and contrast
            int contrast = 0;

            // fct = 1 or 2
            int fct = 2

            if (r > (g + b)/fct)
            {
                r += contrast;
                if (r > 255)
                {
                    r = 255;
                }
            }

            if (g > (r + b)/fct)
            {
                g += contrast;
                if (g > 255)
                {
                    g = 255;
                }
            }

            if (b > (g + r)/fct)
            {
                b += contrast;
                if (b > 255)
                {
                    b = 255;
                }
            }
*/

            // COLORREF is defined as an unsigned long in Wingdi.h
            unsigned long gdiColorRef = RGB(r, g, b);   // Set a GDI COLORREF value.

            // Set the color object to the COLORREF value.
            gdipColor.SetFromCOLORREF(gdiColorRef);

            mergedBitmap.SetPixel(i, k, gdipColor);

       }
   }
   // fill the image with color
   std::cout << "\rMerging images... 100% done. \r\n";

   std::cout << "Saving file...";




   //Save to JPG
   CLSID pngClsid;
   GetEncoderClsid(L"image/jpeg", &pngClsid);
   mergedBitmap.Save(L"merged.jpg", &pngClsid, NULL);

   std::cout << "\rDone                                \r\n\r\n";
   //gpBitmap



   //CLSID pngClsid;
   //CLSIDFromString();
   //GetEncoderClsid(L"image/png", &pngClsid);
   //gpBitmap->Save(L"newfile.bmp",);


/*
bmp: {557cf400-1a04-11d3-9a73-0000f81ef32e}
jpg: {557cf401-1a04-11d3-9a73-0000f81ef32e}
gif: {557cf402-1a04-11d3-9a73-0000f81ef32e}
tif: {557cf405-1a04-11d3-9a73-0000f81ef32e}
png: {557cf406-1a04-11d3-9a73-0000f81ef32e}


image/bmp  : {557cf400-1a04-11d3-9a73-0000f81ef32e}
image/jpeg : {557cf401-1a04-11d3-9a73-0000f81ef32e}
image/gif  : {557cf402-1a04-11d3-9a73-0000f81ef32e}
image/tiff : {557cf405-1a04-11d3-9a73-0000f81ef32e}
image/png  : {557cf406-1a04-11d3-9a73-0000f81ef32e}


*/
   system ("pause");
   return 0;
}
