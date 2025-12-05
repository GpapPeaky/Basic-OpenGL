#include "OGL_Cube.hpp"

void OGL_CreateCubeVertexObjectT(OGL_VertexObject& object)
{
    /* 24 vertices (6 faces × 4 vertices) */
    /* Each vertex: position (3) + color (3) + texCoord (2) + normal (3) = 11 floats */
    const GLfloat vertices[] = {
        // FRONT face  (normal 0,0,1)
        -0.5f,-0.5f, 0.5f,  1,0,0,  0,0,  0,0,1,
         0.5f,-0.5f, 0.5f,  0,1,0,  1,0,  0,0,1,
         0.5f, 0.5f, 0.5f,  0,0,1,  1,1,  0,0,1,
        -0.5f, 0.5f, 0.5f,  1,1,0,  0,1,  0,0,1,

        // BACK face (normal 0,0,-1)
        -0.5f,-0.5f,-0.5f,  1,0,1,  1,0,  0,0,-1,
         0.5f,-0.5f,-0.5f,  0,1,1,  0,0,  0,0,-1,
         0.5f, 0.5f,-0.5f,  1,1,1,  0,1,  0,0,-1,
        -0.5f, 0.5f,-0.5f,  0,0,0,  1,1,  0,0,-1,

        // LEFT face (normal -1,0,0)
        -0.5f,-0.5f,-0.5f,  1,0,0,  0,0,  -1,0,0,
        -0.5f,-0.5f, 0.5f,  0,1,0,  1,0,  -1,0,0,
        -0.5f, 0.5f, 0.5f,  0,0,1,  1,1,  -1,0,0,
        -0.5f, 0.5f,-0.5f,  1,1,0,  0,1,  -1,0,0,

        // RIGHT face (normal 1,0,0)
         0.5f,-0.5f,-0.5f,  1,0,1,  1,0,  1,0,0,
         0.5f,-0.5f, 0.5f,  0,1,1,  0,0,  1,0,0,
         0.5f, 0.5f, 0.5f,  1,1,1,  0,1,  1,0,0,
         0.5f, 0.5f,-0.5f,  0,0,0,  1,1,  1,0,0,

        // TOP face (normal 0,1,0)
        -0.5f, 0.5f, 0.5f,  1,0,0,  0,1,  0,1,0,
         0.5f, 0.5f, 0.5f,  0,1,0,  1,1,  0,1,0,
         0.5f, 0.5f,-0.5f,  0,0,1,  1,0,  0,1,0,
        -0.5f, 0.5f,-0.5f,  1,1,0,  0,0,  0,1,0,

        // BOTTOM face (normal 0,-1,0)
        -0.5f,-0.5f, 0.5f,  1,0,1,  0,0,  0,-1,0,
         0.5f,-0.5f, 0.5f,  0,1,1,  1,0,  0,-1,0,
         0.5f,-0.5f,-0.5f,  1,1,1,  1,1,  0,-1,0,
        -0.5f,-0.5f,-0.5f,  0,0,0,  0,1,  0,-1,0
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

    const GLsizei stride = 11 * sizeof(GLfloat);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));

    // texCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(GLfloat)));

    // normal
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(GLfloat)));

    glBindVertexArray(0);
}

void OGL_CreateCubeVertexObjectFC(OGL_VertexObject& object)
{
    // 24 vertices (6 faces × 4 vertices)
    const GLfloat vertices[] = {
        // FRONT face (normal: 0,0,1)
        -0.5f,-0.5f, 0.5f,  1,0,0,  0,0,  0,0,1,
         0.5f,-0.5f, 0.5f,  0,1,0,  1,0,  0,0,1,
         0.5f, 0.5f, 0.5f,  0,0,1,  1,1,  0,0,1,
        -0.5f, 0.5f, 0.5f,  1,1,0,  0,1,  0,0,1,

        // BACK face (0,0,-1)
        -0.5f,-0.5f,-0.5f,  1,0,1,  1,0,  0,0,-1,
         0.5f,-0.5f,-0.5f,  0,1,1,  0,0,  0,0,-1,
         0.5f, 0.5f,-0.5f,  1,1,1,  0,1,  0,0,-1,
        -0.5f, 0.5f,-0.5f,  0,0,0,  1,1,  0,0,-1,

        // LEFT face (-1,0,0)
        -0.5f,-0.5f,-0.5f,  1,0,0,  0,0,  -1,0,0,
        -0.5f,-0.5f, 0.5f,  0,1,0,  1,0,  -1,0,0,
        -0.5f, 0.5f, 0.5f,  0,0,1,  1,1,  -1,0,0,
        -0.5f, 0.5f,-0.5f,  1,1,0,  0,1,  -1,0,0,

        // RIGHT face (1,0,0)
         0.5f,-0.5f,-0.5f,  1,0,1,  1,0,  1,0,0,
         0.5f,-0.5f, 0.5f,  0,1,1,  0,0,  1,0,0,
         0.5f, 0.5f, 0.5f,  1,1,1,  0,1,  1,0,0,
         0.5f, 0.5f,-0.5f,  0,0,0,  1,1,  1,0,0,

        // TOP face (0,1,0)
        -0.5f, 0.5f, 0.5f,  1,0,0,  0,1,  0,1,0,
         0.5f, 0.5f, 0.5f,  0,1,0,  1,1,  0,1,0,
         0.5f, 0.5f,-0.5f,  0,0,1,  1,0,  0,1,0,
        -0.5f, 0.5f,-0.5f,  1,1,0,  0,0,  0,1,0,

        // BOTTOM face (0,-1,0)
        -0.5f,-0.5f, 0.5f,  1,0,1,  0,0,  0,-1,0,
         0.5f,-0.5f, 0.5f,  0,1,1,  1,0,  0,-1,0,
         0.5f,-0.5f,-0.5f,  1,1,1,  1,1,  0,-1,0,
        -0.5f,-0.5f,-0.5f,  0,0,0,  0,1,  0,-1,0
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

    const GLsizei stride = 11 * sizeof(GLfloat);

    glEnableVertexAttribArray(0); // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    glEnableVertexAttribArray(1); // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2); // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(GLfloat)));

    glEnableVertexAttribArray(3); // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(GLfloat)));

    glBindVertexArray(0);
}
