#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    NewColorHex(0xffffff);
    CursorPosition = {0, 0};
}
//write
void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff){
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color.HexColor;
                }

        }
        fontPtr++;
    }
}
void BasicRenderer::Print(const char* str){
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > TargetFramebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}
void BasicRenderer::PrintLine(const char* str){
    Print(str);
    CursorPosition = {0, CursorPosition.Y + 16};
}
//Aadvance write
void BasicRenderer::AadvancePutChar(char chr, unsigned int xOff, unsigned int yOff, unsigned int size){    
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                for(int i = 0; i < size; ++i)
                {
                    for(int j = 0; j < size; ++j)              
                    {
                        *(unsigned int*)(pixPtr + (x + j) + ((y + i) * TargetFramebuffer->PixelsPerScanLine)) = color.HexColor;
                    }
                }
            }

        }
        fontPtr++;
    }
}
void BasicRenderer::AadvancePrint(const char* str, unsigned int size){
    
    char* chr = (char*)str;
    while(*chr != 0){
        AadvancePutChar(*chr, CursorPosition.X, CursorPosition.Y, size);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > TargetFramebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}
//colors
void BasicRenderer::NewColorRGB(int r, int g, int b){
    color.r = r;
    color.g = g;
    color.b = b;

    color.HexColor = ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}
void BasicRenderer::NewColorHex(unsigned int Hex){
    color.HexColor = Hex;

    color.r = ((Hex >> 16) & 0xFF);
    color.g = ((Hex >> 8) & 0xFF); 
    color.b = ((Hex) & 0xFF);
}
//pixels
void BasicRenderer::Pixel(unsigned int x, unsigned int y){
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color.HexColor;
}
void BasicRenderer::PixelSqr(unsigned int x, unsigned int y, unsigned int size, bool R, bool G, bool B){
    unsigned int Lx = CursorPosition.X;
    unsigned int Ly = CursorPosition.Y;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {

            //NewColorRGB(255 -(i + j)*R, 255 -(i + j)*G, 255 -(i + j)*B);
            NewColorRGB((i + j)*R, (i + j)*G, (i + j)*B);
            if(CursorPosition.X > TargetFramebuffer->Width || CursorPosition.Y > TargetFramebuffer->Height){
                continue;
            }

            Pixel(CursorPosition.X, CursorPosition.Y);
            ++CursorPosition.X;
        }
        CursorPosition.X = Lx;
        ++CursorPosition.Y;
    }

    CursorPosition.X = Lx;
    CursorPosition.Y = Ly;
}
void BasicRenderer::SqrBackGround(unsigned int size){
    bool r = true,g = true,b = true;

    for(int i = 0; i < TargetFramebuffer->Height / size; ++i)
    {
        for(int j = 0; j < TargetFramebuffer->Width / size; ++j)
        {
            PixelSqr(CursorPosition.X, CursorPosition.Y, size, r,g,b);
            CursorPosition.X += size;
            r = !g;
            g = !b;
            b = !r;
        }
        CursorPosition.X = 0;
        CursorPosition.Y += size;
    }
}