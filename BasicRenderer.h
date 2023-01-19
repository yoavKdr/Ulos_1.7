#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"
#include "Colors.h"

class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    NewColor color;

    //write
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void Print(const char* str);
    void PrintLine(const char* str);
    //Aadvance write
    void AadvancePutChar(char chr, unsigned int xOff, unsigned int yOff, unsigned int size);
    void AadvancePrint(const char* str, unsigned int size);
    //colors
    void NewColorHex(unsigned int Hex);
    void NewColorRGB(int r, int g, int b);
    //Pixels  
    void Pixel(unsigned int x, unsigned int y);
    void PixelSqr(unsigned int x, unsigned int y, unsigned int size, bool R, bool G, bool B);
    void SqrBackGround(unsigned int size);

};
