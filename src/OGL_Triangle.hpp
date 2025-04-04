#include "../ThirdParty/GLAD/include/glad/glad.h" /* OpenGL */

#include "OGL_Object.hpp"

#include <vector> /* For the vertices */

#pragma once

/**
 * @brief Creates the vertices of a triangle (fixed)
 * 
 * @param object Containts both the VBO and VAO
 * 
 * @warning ## This should no be used as we have agreed
 * that all OGL_VertexObjects' VBO's should have position
 * AND colour in each vertex, this function only creates
 * vertices with position data and NOT RGB values. Use
 * OGL_TriangleVertexFC(...) instead.
 * 
 * @note VBO, and VAO hold only positions, not colours
 */
void OGL_CreateTriangleVertexF(OGL_VertexObject& object);

/**
 * @brief Creates the vertices of a triangle (fixed, coloured)
 * 
 * @param object Containts both the VBO and VAO
 * 
 * @note VBO, and VAO hold positions and colours
 */
void OGL_CreateTriangleVertexFC(OGL_VertexObject& object);