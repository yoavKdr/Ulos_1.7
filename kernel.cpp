
#include <stdint.h>
#include "BasicRenderer.h"
#include "cstr.h"


extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font){

    BasicRenderer Console = BasicRenderer(framebuffer, psf1_font);

    Console.SqrBackGround(35);

    Console.NewColorRGB(255,255,255);
    Console.CursorPosition = {0, 0};

    Console.AadvancePrint("Bolbol", 3);

    return ;
}