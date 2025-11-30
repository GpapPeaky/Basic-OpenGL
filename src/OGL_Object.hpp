#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"    /* SDL2 */
#include "../ThirdParty/GLAD/include/glad/glad.h"   /* GLAD */
#include "../ThirdParty/glm/glm.hpp"                /* GLM */
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"

#include <iostream> /* Printing */
#include <vector>   /* For vectors */

/**
 * @brief Contains The Vertex Buffer Objects, Vertex Array Object
 * and Index Array Object (as well as the vertices count for
 * some small optimizations). This object type is polymorhpic
 * and we can basically use it for displaying both quads/triangles
 * and textured quads.
 * 
 * @warning ##  In order to use these objects, we need references
 * and not pointers with allocated memory (for some reason I don't
 * know).
 */
typedef struct OGL_VertexObject{
    GLuint VAO; /* The vertex array object:
        This tells us how the bound VBO will be used,
        which means we can have many VBOs for one VAO. It
        appears to not be a good idea.
    */
    GLuint VBO; /* The vertex buffer object:
        It is important to note
        that each vertex in the VBO will consist of 3 floats, 3 for position, 3 for colour
        else the OGL_VertexObject will be nullified. Objects that only have 3 floats
        in each vertex, have only position data, and not colour data, they 
        are used for testing, OGL_VertexObject can ALSO have texture coordinates
        in order to load bitmaps onto quads, so we have another 'field'
        inside the VBO that will consist of texture coordinates
        (see: OGL_TextureQuad.cpp l:7) so we have this format:

                  // pos         // colour      // texture
        vertex 1: X1, Y1, Z1,    R1, G1, B1,    S1, T1 
        vertex 2: X2, Y2, Z2,    R2, G2, B2,    S2, T2 

        3 + 3 + 2 floats! */

    /* TODO: Add TRS/MVP? */

    /* By adding more 'VBOs' we can give more data to each object */
    /* And if it is not required, we simply do not engage with the fields */
    /* We can omit the extra VBO by only using one */
    // GLuint RGBVBO; /* colours: vertex buffer object */
    GLuint IBO; /* Index Buffer Object, for vertices rendering order (we can skip vertices repeating in quads like this) */
    Uint8 verticesCount; /* Count of vertices for when the drawing function is called */
}OGL_VertexObject;

/**
 * @brief Main object type, required pos/rot/scl
 * data in the CPU for updating
 */
typedef struct OGL_Object{
    OGL_VertexObject mesh; /* Mesh, GPU data */

    /* CPU data, TRS to get the model */

    float position[3];
    float rotation[3];  
    float scale[3];
}OGL_Object;
