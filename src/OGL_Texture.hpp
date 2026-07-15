#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"    /* SDL2 */
#include "../ThirdParty/GLAD/include/glad/glad.h"   /* GLAD */

typedef struct OGL_Texture{
    int width = 0;
    int height = 0;
    unsigned char* cpuPixels = nullptr;
    int channels = 0;
    GLuint texture = 0;
}OGL_Texture;