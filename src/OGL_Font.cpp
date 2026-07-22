#include "OGL_Font.hpp"

FT_Library OGL_InitFreeType(void){
    FT_Library ft;
    if (FT_Init_FreeType(&ft)){
        std::fprintf(stderr, "OGL_ERR: Could not init FreeType Library\n");
    }

    return ft;
}

FT_Face OGL_LoadFont(FT_Library ft, std::string fontName, unsigned int height){
    FT_Face face;
    if (FT_New_Face(ft, fontName.c_str(), 0, &face)){
        std::fprintf(stderr, "OGL_ERR: Failed to load font\n");  
    }

    FT_Set_Pixel_Sizes(face, 0, height); // Dynamically finds out what the width of the glyph will be based on the height

    return face;
}

