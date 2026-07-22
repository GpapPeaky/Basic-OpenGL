#pragma once

#include <string>
#include <iostream>

#include "../ThirdParty/freetype-2.14.3/include/freetype/freetype.h"
#include FT_FREETYPE_H  

/**
 * @brief Initialises an FT library for font loading and rendering
 * 
 * @returns The newly created FT_Library object
 */
FT_Library OGL_InitFreeType(void);

/**
 * @brief Loads a font into a new FT face
 * 
 * @param ft Font library
 * @param fontName Name of font inside the root folder
 * @param height Glyph height
 * 
 * @returns The newly created FT_Face object
 */
FT_Face OGL_LoadFont(FT_Library ft, std::string fontName, unsigned int height);