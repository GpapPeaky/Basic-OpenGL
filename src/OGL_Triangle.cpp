#include "OGL_Triangle.hpp"

void OGL_CreateTriangleVertexF(OGL_VertexObject& object){
    object.verticesCount = 3; /* Triangle has 3 vertices */

    /* Lives on the CPU */
    /* We can have more attributes in here, for example vertex1 can also have R,G,B,A floats */
    const std::vector<GLfloat> vertexPos{
        /*  x      y     z */
        -0.5f, -0.3f, 0.5f, // Vertex 1 
        0.5f, -0.1f, 0.5f,  // Vertex 2
        0.3f, 0.3f, 0.8f,   // Vertex 3
    };
    /* z coord is ommited in 2D */

    /* VAO, lives in the GPU */
    /* The VAO tells us about the attributes of the object */
    glGenVertexArrays(1, &object.VAO);
    /* We select that array */
    glBindVertexArray(object.VAO);

    /* We now start generating the VBO */
    /* We only want the position index, since we have no specified colour here */
    glGenBuffers(1, &object.VBO);
    /* We select that buffer */
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    /* Give our data to the VBO */
    glBufferData(GL_ARRAY_BUFFER, vertexPos.size() * sizeof(GLfloat), // Size of data
                vertexPos.data(), // Data 
                GL_STATIC_DRAW); // Give OpenGL, a "taste" of what we will use the VBO for

    const std::vector<GLuint> indexBuffer { 0, 1, 2 }; /* Create the index buffer */

    /* Generate the rendering order, which is calculated wit the index buffer object */
    glGenBuffers(1, &object.IBO);
    /* Not the array buffer, but the element array/index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint),
                indexBuffer.data(),
                GL_STATIC_DRAW);

    /* Enable attributes of the vertex (position for example) */
    /* We tell OpenGL, how to use the VAO */
    /* Specifically, we link the index of the data in VAO, to the corresponding data in the VBO */
    /* We enable index 0 */
    glEnableVertexAttribArray(0);
    /* Configure the attributes of the vertex, and how we will move inside of it */
    glVertexAttribPointer(0, // VAO index, and how to handle it
                        3, // Number of elements in each vertex
                        GL_FLOAT, // type of element
                        GL_FALSE,
                        sizeof(GLfloat) * 3, // Bytes per element
                        (void*)0); // Offset

    /* We can set a new VBO for the R,G,B data (see OGL_TriangleVertexFC(...))*/

    /* Cleanup, to close the arrays/buffers */
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

    return;
}

void OGL_CreateTriangleVertexFC(OGL_VertexObject& object){
    object.verticesCount = 3; /* Triangle has 3 vertices */

    /* Lives on the CPU */
    /* We can have more attributes in here, for example vertex1 can also have R,G,B,A floats */
    /* We will remove the extra vector */
    /* And combine the buffer objects, just like the VAO */
    /* Tightly packed data format */
    
    const std::vector<GLfloat> vertices{
        /* Rendering is completed with CCW order (LV.RV.TV) */
        /*  x      y     z */
        /* R     G      B */
        -0.5f, -0.5f, 0.0f, // Vertex 1 pos LV
        0.0f, 0.0f, 1.0f, // Vertex 1 colours

        0.5f, -0.5f, 0.0f,  // Vertex 2 pos RV
        0.0f, 1.0f, 0.0f, // Vertex 2 colours

        -0.5f, 0.5f, 0.0f,   // Vertex 3 pos TV
        1.0f, 0.0f, 0.0f // Vertex 3 colours
    };
    /* z coord is ommited in 2D */

    /* We combine both positions and rgb in one VBO */
    // const std::vector<GLfloat> vertexRGB{
    //     /* R     G      B */
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f
    // };

    /* VAO, lives in the GPU */
    /* The VAO tells us about the attributes of the object */
    glGenVertexArrays(1, &object.VAO);
    /* We select that array */
    glBindVertexArray(object.VAO);

    /* Vertex position VBO */

    /* We now start generating the VBO */
    glGenBuffers(1, &object.VBO);
    /* We select that buffer, we specifically pass the position VBO */
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    /* Give our data to the VBO */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), // Size of data , doesn't change since these are all floats
                vertices.data(), // Data 
                GL_STATIC_DRAW); // Give OpenGL, a hint of what we will use the data for

    const std::vector<GLuint> indexBuffer { 0, 1, 2 }; /* Create the index buffer */

    /* Generate the rendering order, which is calculated wit the index buffer object */
    glGenBuffers(1, &object.IBO);
    /* Not the array buffer, but the element array/index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint),
                indexBuffer.data(),
                GL_STATIC_DRAW);

    /* Enable attributes of the vertex (position for example) */
    /* We tell OpenGL, how to use the VAO */
    /* Specifically, we link the index of the data in VAO, to the corresponding data in the VBO */
    /* We enable index 0 */
    glEnableVertexAttribArray(0);
    /* Configure the attributes of the vertex, and how we will move inside of it */
    glVertexAttribPointer(0, // VAO index, and how to handle it
                        3, // Number of elements in each vertex
                        GL_FLOAT, // type of element
                        GL_FALSE, // Non normalised information
                        sizeof(GLfloat) * 6, // Strides for next element, byte offset, we hop 3 floats for the next x,y,z positions
                        (GLvoid*)0); // Initial offset

    /* Vertex colour VBO */

    /* We can omit the extra VBO, by adding the rgb in the first one */
    // /* We genereate the RGB VBO */
    // glGenBuffers(1, &object.RGBVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, object.RGBVBO);
    // glBufferData(GL_ARRAY_BUFFER, vertexRGB.size() * sizeof(GLfloat),
    //             vertexRGB.data(),
    //             GL_STATIC_DRAW);

    /* We tell OpenGL, how to use the VAO */
    /* Specifically, we link the index of the data in VAO, to the corresponding data in the VBO */
    /* We enable index 1 (RGB values) */
    glEnableVertexAttribArray(1);
    /* Configure the attributes of the vertex, and how we will move inside of it */
    glVertexAttribPointer(1, // VAO index, and how to handle it
                        3, // r, g, b
                        GL_FLOAT, // type of element
                        GL_FALSE, // Non normalised information
                        sizeof(GLfloat) * 6, // Bytes per element. We use this to access the rgb right after the positions (3 floats again)
                        (GLvoid*)(sizeof(GLfloat) * 3)); // Initial offset of the rgb vertices locations

    /* VBO structure: */
    // VBO
    // WARN: Stride: We need to jump 6 things NOT 3
    // if we add a new attribute, we will have to update the strides as well as the initial offsets, ect...
    // This format can be seen in the vertices vector
    // x1,y1,z1 _ r1,g1,b1 | x2,y2,z2 _ r2,g2,b2 _ ...

    /* Cleanup, to close the arrays/buffers */
    glBindVertexArray(0);
    /* We disable the pointers to the objects attributes */
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    return;
}
