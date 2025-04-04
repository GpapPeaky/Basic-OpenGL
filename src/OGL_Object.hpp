#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"    /* SDL2 */
#include "../ThirdParty/GLAD/include/glad/glad.h"   /* GLAD */

#include <iostream> /* Printing */
#include <vector>   /* For vectors */

/**
 * @brief Contains The Vertex Buffer Objects and Vertex Array Object
 * 
 * @warning ##  In order to use these objects, we need regferences
 * and not pointers with allocated memory (for some reason I don't
 * know).
 */
typedef struct OGL_VertexObject{
    GLuint VAO; /* Vertex array object */
    GLuint VBO; /* positions: vertex buffer object, It is important to note
    that each vertex in the VBO will consist of 3 floats, 3 for position, 3 for colour
    else the OGL_VertexObject will be nullified. Objects that only have 3 floats
    in each vertex, have only position data, and not colour data, they 
    are used for testing, OGL_VertexObject can ALSO have texture coordinates
    in order to load bitmaps onto quads, so we have another 'field'
    inside the VBO that will consist of texture coordinates
    (see: OGL_TextureQuad.cpp l:7) so we have this format:
    
    // pos      // colour   // texture
    X, Y, Z,    R, G, B,    S, T 
    
    3 + 3 + 2 floats! */

    /* By adding more 'VBOs' we can give more data to each object */
    /* And if it is not required, we simply do not engage with the fields */
    /* We can omit the extra VBO by only using one */
    // GLuint RGBVBO; /* colours: vertex buffer object */
    GLuint IBO; /* Index Buffer Object, for vertices rendering order (we can skip vertices repeating in quads like this) */
    Uint8 verticesCount; /* Count of vertices for when the drawing function is called */
}OGL_VertexObject;

/**
 * @brief Updates the position of an object by 
 * modifying it's VBO, specifically the vertices that hold
 * position data and not colour
 * 
 * @param object Object to reposition
 * @param dx X coordinate change
 * @param dy Y coordinate change
 * @param dz Z coordinate change
 * 
 * @note Keep in mind that the center is not
 * in the top left corner of the screen but at
 * the center of it
 */
void OGL_UpdateObjectPosition(OGL_VertexObject& object, GLfloat dx, GLfloat dy, GLfloat dz);
