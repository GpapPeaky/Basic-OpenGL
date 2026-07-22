#include "OGL_Render.hpp"

OGL_Camera* OGL_RenderView;

void OGL_BindCameraToRenderView(OGL_Camera* cam){
    OGL_RenderView = cam;

    return;
}

void OGL_PreDraw(GLuint graphicsPipeline){
    glViewport(0, 0, SDL2_WinWidth, SDL2_WinHeight);

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    /* TexQuad disappearing issue fix, quad needs to be 2-faced */
    /* Kinda choppy */
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);
    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

    glUseProgram(graphicsPipeline);
}

void OGL_PreDrawText(GLuint graphicsPipeline){
    glUseProgram(graphicsPipeline);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    OGL_PreDraw(object->mat.shader);

    /* Bind tex */
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object->mat.texture.texture);

    /* Send model TRS */
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uTrans"),      1, object->position.data());
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uRotate"),     1, object->rotation.data());
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uScale"),      1, object->scale.data());

    /* Send camera matrices */
    glUniformMatrix4fv(glGetUniformLocation(object->mat.shader, "uView"), 1, GL_FALSE, glm::value_ptr(OGL_GetViewMatrix(OGL_RenderView)));
    glUniformMatrix4fv(glGetUniformLocation(object->mat.shader, "uProj"), 1, GL_FALSE, glm::value_ptr(OGL_GetProjMatrix(OGL_RenderView)));

    /* Send color */
    glUniform4fv(glGetUniformLocation(object->mat.shader, "uColor"),      1, object->mat.diffuse.data()); /* TODO: Remove this, use ONLY diffuse from lighting */

    /* Send light, for now static */
    glUniform3fv(glGetUniformLocation(object->mat.shader,  "uLightDir"),         1,      glm::value_ptr(glm::vec3(0.0f, 4.0f, 0.0f)));
    glUniform3fv(glGetUniformLocation(object->mat.shader,  "uLightColor"),       1,      glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform1f(glGetUniformLocation (object->mat.shader,  "uLightIntensity"),   2.0f);
    
    /* Time info */
    glUniform1f(glGetUniformLocation (object->mat.shader,  "uDeltaTime"),        OGL_GameDt);
    glUniform1f(glGetUniformLocation (object->mat.shader,  "uAccumulatedTime"),  OGL_GameTime);

    /* Send object material */
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uMatAmbientColor"),  1,  object->mat.ambient.data());
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uMatDiffuseColor"),  1,  object->mat.diffuse.data());
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uMatSpecularColor"), 1,  object->mat.specular.data());
    glUniform3fv(glGetUniformLocation(object->mat.shader, "uMatEmitColor"),     1,  object->mat.emit.data());
    glUniform1f(glGetUniformLocation (object->mat.shader,  "uMatEmitIntensity"),    object->mat.emissiveness);
    glUniform1f(glGetUniformLocation (object->mat.shader,  "uMatShininess"),        object->mat.shininess);
    
    OGL_DrawObject(object->mesh);
    
    return;
}

void OGL_RenderVisitChildren(OGL_ONode* parent){
    if (!parent->active) return; /* Parent is NOT active, so children also aren't */
    if (!parent->visible) return; /* Parent is NOT visible, so children also aren't, updates will occur in invisible objects! */

    OGL_Render(parent->o); /* Render the parent, currently visiting node */
    
    for(auto c : parent->children){
        OGL_RenderVisitChildren(c);
    }
}

