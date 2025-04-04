#include "OGL_TextureQuad.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb_image/stb_image.h"  /* Image loading */

void OGL_CreateTextureQuad(OGL_VertexObject& object){
    object.verticesCount = 6; /* 6 vertices for 2 triangles */

    // In OpenGL, the origin is at the center and the y-axis is flipped, negatives at the top.
    // in bitmaps the origin is at the top left!

    // Vertex data: position (x, y, z), color (r, g, b), texture coords (s, t)
    const std::vector<GLfloat> vertices = {
        // Positions                   // Colors          // TexCoords
        -1.0f, -1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Bottom Left
         1.0f, -1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // Bottom Right
         1.0f,  1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // Top Right
        -1.0f,  1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  0.0f, 0.0f   // Top Left
    };

    /* Index buffer (EBO/IBO) */
    /* This can sometimes break things */
    const std::vector<GLuint> indices {
        0, 1, 2,
        0, 2, 3 };

    /* Generate and bind VAO */
    glGenVertexArrays(1, &object.VAO);
    glBindVertexArray(object.VAO);

    /* Generate and bind VBO */
    glGenBuffers(1, &object.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    /* Generate and bind IBO */
    glGenBuffers(1, &object.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    /* Define vertex attributes */
    
    // Position Attribute (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);

    // Color Attribute (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));

    // Texture Coordinate Attribute (location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));

    /* Unbind VAO (good practice) */
    glBindVertexArray(0);

    /* Disable attributes */
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    return;
}

void OGL_LoadBitmapToObject(OGL_VertexObject& object, const char* bitmap){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); /* Bind the texture, and it's type */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, channels;
    unsigned char* data = stbi_load(bitmap, &w, &h, &channels, 0);

    if(data){
        if(w > 0 && h > 0){
            GLenum format = (channels == 3) ? GL_RGB : GL_RGBA; /* See what colour format we can use based on the bitmap provided */

            /* Upload texture to OpenGL */
            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D); /* Texture scaling mipmaps */
        }
    }else{
        std::fprintf(stderr, "OGL_ERR: Failed to load bitmap %s (%s)\n", bitmap, stbi_failure_reason());
    }

    /* Free the data here */
    stbi_image_free(data);

    /* Pass the proccessed data onto the VBO */
    object.VBO = texture;

    return;
}
