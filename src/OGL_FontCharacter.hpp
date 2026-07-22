#pragma once

#include <map>
#include "../ThirdParty/glm/glm.hpp"
#include "../ThirdParty/GLAD/include/glad/glad.h"

#include "OGL_Font.hpp"
#include "OGL_Object.hpp"
#include "OGL_Render.hpp"

typedef struct OGL_Character{
    unsigned int tid;        // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
}OGL_Character; // Used by the FreeType library, easier rendering

/**
 * @brief Load characters based on a font face
 * 
 * @param face Loaded font to read from
 * 
 * @returns A map that transforms a character into an OGL_Character based on the face  
 */
std::map<char, OGL_Character> OGL_LoadCharacters(FT_Face face);

/**
 * @brief Renders text
 * 
 * @param obj Object tied to font rendering
 * @param text Text string
 * @param x X coord in screen
 * @param y Y coord in screen
 * @param scale Render scaling
 * @param color Color of text
 * @param characters Character glyphs data
 */
void OGL_RenderText(OGL_Object &obj, std::string text, float x, float y, float scale, glm::vec3 color, std::map<char, OGL_Character>& characters);