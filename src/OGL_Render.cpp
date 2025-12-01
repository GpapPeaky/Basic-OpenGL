#include "OGL_Render.hpp"

OGL_Camera* OGL_RenderView;

void OGL_BindCameraToRenderView(OGL_Camera* cam){
    OGL_RenderView = cam;

    return;
}

GLuint OGL_CreateGraphicsPipeline(const std::string& vs, const std::string& fs){
    return OGL_CreateShaderProgram(vs, fs);;
}

void OGL_PreDraw(GLuint graphicsPipeline){
    /* Save the current OpenGL state */
    GLint depthTestEnabled, cullFaceEnabled;
    glGetIntegerv(GL_DEPTH_TEST, &depthTestEnabled);
    glGetIntegerv(GL_CULL_FACE, &cullFaceEnabled);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    glViewport(0, 0, SDL2_WinWidth, SDL2_WinHeight); /* Viewport is also important, and can mess things up */

    glUseProgram(graphicsPipeline); /* Pipeline previously created */

    /* Reset to the previous OpenGL state */
    if(depthTestEnabled){
        glEnable(GL_DEPTH_TEST);
    }
    
    if(cullFaceEnabled){
        glEnable(GL_CULL_FACE);
    }

    return;
}

void OGL_Draw(OGL_VertexObject* object){
    /* Select the array and buffer vertex objects */
    glBindVertexArray(object->VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* Draw the selected arrays */
    /* We need to update the 3 to 6 if we are rendering a quad, instead of a triangle */
    /* 6 Works for triangles as well */
    /* For non index array objects */
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    /* For index arrays */
    glDrawElements(GL_TRIANGLES,
                object->verticesCount, // How many "items" / vertices to render
                GL_UNSIGNED_INT, // Type
                0);

    glBindVertexArray(0); /* Unibind */

    return;
}

void OGL_DrawObject(OGL_VertexObject* object){
    OGL_Draw(object); /* We can call it like this */

    return;
}

void OGL_SetScreenBackground(float r, float g, float b, float a){
    /* Screen background, this has to be done seperately
    before other rendering functions, since the buffer is
    overwritten and cleared, when called in pre-draw */
    glClearColor(r, g, b, a);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    return;
}

void OGL_Render(OGL_Object* object){
    OGL_PreDraw(object->shader);

    /* Send model TRS */
    glUniform3fv(glGetUniformLocation(object->shader, "uTrans"),     1, object->position);
    glUniform3fv(glGetUniformLocation(object->shader, "uRotate"),    1, object->rotation);
    glUniform3fv(glGetUniformLocation(object->shader, "uScale"),     1, object->scale);

    /* Send camera matrices */
    glUniformMatrix4fv(glGetUniformLocation(object->shader, "uView"), 1, GL_FALSE, glm::value_ptr(OGL_GetViewMatrix(OGL_RenderView)));
    glUniformMatrix4fv(glGetUniformLocation(object->shader, "uProj"), 1, GL_FALSE, glm::value_ptr(OGL_GetProjMatrix(OGL_RenderView)));

    /* Send color */
        glUniform4fv(glGetUniformLocation(object->shader, "uColor"), 1, object->color);

    OGL_DrawObject(object->mesh);
    
    return;
}
