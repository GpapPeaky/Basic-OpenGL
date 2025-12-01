#include "OGL_Cube.hpp"

void OGL_CreateCubeVertexObject(OGL_VertexObject& object) {
    // Cube vertices (8 unique corners)
    const std::vector<GLfloat> vertices = {
        /* Positions */         /* Colors */
        -0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, /* 0 */
         0.5f, -0.5f, -0.5f, 0.f, 1.f, 0.f, /* 1 */
         0.5f,  0.5f, -0.5f, 0.f, 0.f, 1.f, /* 2 */
        -0.5f,  0.5f, -0.5f, 1.f, 1.f, 0.f, /* 3 */
        -0.5f, -0.5f,  0.5f, 1.f, 0.f, 1.f, /* 4 */
         0.5f, -0.5f,  0.5f, 0.f, 1.f, 1.f, /* 5 */
         0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, /* 6 */
        -0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f  /* 7 */
    };

    const std::vector<GLuint> indices = {
        /* Front face */
        4, 5, 6,
        6, 7, 4,
        /* Back face */
        0, 3, 2,
        2, 1, 0,
        /* Left face */
        0, 4, 7,
        7, 3, 0,
        /* Right face */
        1, 2, 6,
        6, 5, 1,
        /* Top face */
        3, 7, 6,
        6, 2, 3,
        /* Bottom face */
        0, 1, 5,
        5, 4, 0
    };

    object.verticesCount = static_cast<GLuint>(indices.size()); /* 36 indices */
     
    glGenVertexArrays(1, &object.VAO);
    glBindVertexArray(object.VAO);

    glGenBuffers(1, &object.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &object.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
}
