#pragma once

#include "OGL_Object.hpp"                       /* Object abstraction */

#include "OGL_Camera.hpp"

#include "SDL2_InitWin.hpp"                     /* Window data */

#include "OGL_Texture.hpp"

/**
 * @brief Creates a texture quad. Vertices
 * on a texture quad also include another 
 * vertex, with texture coordinates
 * 
 * @param object Where to save the texture quad
 */
void OGL_CreateTextureQuad(OGL_VertexObject& object);

/**
 * @brief Creates a texture quad but foramted specifically for text
 * 
 * @param object Object to save the text quad
 */
void OGL_CreateTextQuad(OGL_VertexObject& object);

/**
 * @brief Loads a texture to the texture quad
 * vertex object
 * 
 * @param object Object to load the bitmap
 * @param bitmap Filename of bitmap
 * 
 * @warning Make sure you have created a texture quad vertex object
 */
void OGL_LoadBitmapToObject(OGL_Object& object, const char* bitmap); /* TODO: Review one by one what this does */

/**
 * @brief Loads a texture to the texture quad
 * vertex object
 * 
 * @param object Object to load the bitmap
 * @param bitmap Filename of bitmap
 * 
 * @warning Make sure you have created a texture quad vertex object
 */
#define OGL_LoadBitmap(o, bmp) OGL_LoadBitmapToObject(o, bmp);

/**
 * @brief Get hovered colour from texture, based on mouse coordinates
 * 
 * @param texture Texture to read pixel from
 * @param model Model of the object
 * @param cam Camera for tranformations
 * 
 * @returns RGB color found
 */
std::array<unsigned char, 3> OGL_GetHoveredColourFromTexture(const OGL_Texture& texture, const glm::mat4& model, OGL_Camera* cam);