#pragma once

#include "OGL_Object.hpp"                       /* Object abstraction */

#include "SDL2_InitWin.hpp"                     /* Window data */

/**
 * @brief Creates a texture quad. Vertices
 * on a texture quad also include another 
 * vertex, with texture coordinates
 * 
 * @param object Where to save the texture quad
 */
void OGL_CreateTextureQuad(OGL_VertexObject& object);

/**
 * @brief Loads a texture to the texture quad
 * vertex object
 * 
 * @param object Object to load the bitmap
 * @param bitmap Filename of bitmap
 * 
 * @warning Make sure you have created a texture quad vertex object
 */
void OGL_LoadBitmapToObject(OGL_VertexObject& object, const char* bitmap); /* TODO: Review one by one what this does */

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
