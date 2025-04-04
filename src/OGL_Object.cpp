#include "OGL_Object.hpp"

void OGL_UpdateObjectPosition(OGL_VertexObject& object, GLfloat dx, GLfloat dy, GLfloat dz){
    GLfloat* vertices; /* Current VBO data (position and colour) */

    glBindBuffer(GL_ARRAY_BUFFER, object.VBO); /* Bind the objects VBO to change */
    vertices = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE); /* Map the VBO to the vertices */

    if(vertices == nullptr){
        std::fprintf(stderr, "Cannot map VBO vertices to update\n");
        return;
    }

    for(size_t i = 0 ; i < object.verticesCount ; i++){
        size_t vertexIndex = i * 6; /* Since each vertex has 6 floats, 3 for position, 3 for colour */

        /* Apply change of position */
        vertices[vertexIndex] += dx;
        vertices[vertexIndex + 1] += dy;
        vertices[vertexIndex + 2] += dz;
    }

    /* Unmap the bufer after applying position changes */
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Update buffer data */
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 6 * object.verticesCount, vertices);

    return;
}
