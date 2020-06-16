/* FILE NAME: IMAGE.H
 * PROGRAMMER: AK5 13631/2
 * PURPOSE: definitions
 * DATE: 27.02.2019
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "def.h"

typedef struct
{
  BYTE B, G, R, A;
} color4;

struct image
{
  color4 * Pixels;
  UINT W, H;
  image() : W(0), H(0), Pixels(NULL)
  {
  }
  BOOL LoadBMP(CHAR* FileName) 
  {
    HBITMAP hBm;

    if ((hBm = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) != NULL)
    {
      INT i;
      DWORD* Bits;
      BITMAP bm;
      BITMAPINFOHEADER bih = { 0 };
      HBITMAP hDib;
      HDC hDC, hMemDC1, hMemDC2;

      hDC = GetDC(NULL);
      hMemDC1 = CreateCompatibleDC(hDC);
      hMemDC2 = CreateCompatibleDC(hDC);
      ReleaseDC(NULL, hDC);

      GetObject(hBm, sizeof(bm), &bm);

      /* Make DIB in memory */
      bih.biSize = sizeof(BITMAPINFOHEADER);
      bih.biBitCount = 32;
      bih.biWidth = bm.bmWidth;
      bih.biHeight = bm.bmHeight;
      bih.biPlanes = 1;

      hDib = CreateDIBSection(NULL, (BITMAPINFO*)&bih, DIB_RGB_COLORS, (VOID**)&Bits, NULL, 0);

      SelectObject(hMemDC1, hBm);
      SelectObject(hMemDC2, hDib);
      BitBlt(hMemDC2, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC1, 0, 0, SRCCOPY);

      W = bm.bmWidth;
      H = bm.bmHeight;
      Pixels = new color4[H * W];

      /* Correct alpha-channel */
      for (i = 0; i < bm.bmWidth * bm.bmHeight; i++)
      {
        *(ULONG*)(Pixels + i) = Bits[i] | 0xFF000000;
        if (Pixels[i].R == 250 && Pixels[i].G == 250 && Pixels[i].B == 250)
          Pixels[i].A = 0;
      }
      //FlipVertical();

      DeleteObject(hDib);
      DeleteObject(hBm);
      DeleteDC(hMemDC1);
      DeleteDC(hMemDC2);
      return TRUE;
    }
    return FALSE;
  };
  
  VOID Free(VOID)
  {
    delete[] Pixels;
    Pixels = NULL;
  }

  ~image() 
  {
    if (Pixels)
      delete[] Pixels;
  };
};


#endif // __IMAGE_H_

/* END OF 'IMAGE.H' FILE */