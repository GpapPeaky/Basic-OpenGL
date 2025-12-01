#include "OGL_Cube.hpp"

void OGL_CreateCubeVertexObjectFC(OGL_VertexObject& object) {
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

void OGL_CreateCubeVertexObjectT(OGL_VertexObject& object)
{
    // 24 vertices (6 faces × 4 vertices)
    const GLfloat vertices[] = {
        // FRONT face
        //  pos              color           uv
        -0.5f,-0.5f, 0.5f,  1,0,0,          0,0,
         0.5f,-0.5f, 0.5f,  0,1,0,          1,0,
         0.5f, 0.5f, 0.5f,  0,0,1,          1,1,
        -0.5f, 0.5f, 0.5f,  1,1,0,          0,1,

        // BACK face
        -0.5f,-0.5f,-0.5f,  1,0,1,          1,0,
         0.5f,-0.5f,-0.5f,  0,1,1,          0,0,
         0.5f, 0.5f,-0.5f,  1,1,1,          0,1,
        -0.5f, 0.5f,-0.5f,  0,0,0,          1,1,

        // LEFT face
        -0.5f,-0.5f,-0.5f,  1,0,0,          0,0,
        -0.5f,-0.5f, 0.5f,  0,1,0,          1,0,
        -0.5f, 0.5f, 0.5f,  0,0,1,          1,1,
        -0.5f, 0.5f,-0.5f,  1,1,0,          0,1,

        // RIGHT face
         0.5f,-0.5f,-0.5f,  1,0,1,          1,0,
         0.5f,-0.5f, 0.5f,  0,1,1,          0,0,
         0.5f, 0.5f, 0.5f,  1,1,1,          0,1,
         0.5f, 0.5f,-0.5f,  0,0,0,          1,1,

        // TOP face
        -0.5f, 0.5f, 0.5f,  1,0,0,          0,1,
         0.5f, 0.5f, 0.5f,  0,1,0,          1,1,
         0.5f, 0.5f,-0.5f,  0,0,1,          1,0,
        -0.5f, 0.5f,-0.5f,  1,1,0,          0,0,

        // BOTTOM face
        -0.5f,-0.5f, 0.5f,  1,0,1,          0,0,
         0.5f,-0.5f, 0.5f,  0,1,1,          1,0,
         0.5f,-0.5f,-0.5f,  1,1,1,          1,1,
        -0.5f,-0.5f,-0.5f,  0,0,0,          0,1
    };

    const GLuint indices[] = {
        0,1,2, 2,3,0,      
        4,5,6, 6,7,4,      
        8,9,10, 10,11,8,   
        12,13,14, 14,15,12,
        16,17,18, 18,19,16,
        20,21,22, 22,23,20 
    };

    object.verticesCount = 36;

    glGenVertexArrays(1, &object.VAO);
    glBindVertexArray(object.VAO);

    glGenBuffers(1, &object.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &object.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const GLsizei stride = 8 * sizeof(GLfloat);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));

    /* texCoord */
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(GLfloat)));

    return;
}
