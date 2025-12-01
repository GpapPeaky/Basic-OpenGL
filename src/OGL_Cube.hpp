#pragma once

#include "OGL_Object.hpp"

/**
 * @brief Create a simple cube object of fixed color, 
 * no (u,v) pair
 *
 * @param object Object to assign the produced vertex array
 */
void OGL_CreateCubeVertexObjectFC(OGL_VertexObject& object);

/**
 * @brief Create a simple cube of specific texture
 * 
 * @param object Object to assign the produced vertex array
 */
void OGL_CreateCubeVertexObjectT(OGL_VertexObject& object);
