#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);

    /* Plane creation*/
    OGL_Object* plane = new OGL_Object;
    plane->mesh = new OGL_VertexObject;
    OGL_CreateCubeVertexObject(*plane->mesh);

    plane->position[0] = 0.f; plane->position[1] = -0.6f; plane->position[2] = 0.f;
    plane->rotation[0] = 0.f; plane->rotation[1] = -0.6f; plane->rotation[2] = 0.f;
    plane->scale[0]    = 10.f; plane->scale[1]    = 0.1f; plane->scale[2]    = 10.f;
    
    /* Obj creation */    
    OGL_Object* obj = new OGL_Object;
    obj->mesh = new OGL_VertexObject;
    OGL_CreateCubeVertexObject(*obj->mesh);
    
    /* Initial object TRS */
    obj->position[0] = 0.f; obj->position[1] = 0.f; obj->position[2] = 0.f;
    obj->rotation[0] = 0.f; obj->rotation[1] = 0.f; obj->rotation[2] = 0.f;
    obj->scale[0]    = 1.f; obj->scale[1]    = 1.f; obj->scale[2]    = 1.f;
    
    /* Load bitmap to the object's render mesh */
    OGL_LoadBitmapToObject(*obj->mesh, "assets/pn003.bmp");

    /* Controller creation */
    OGL_Controller* ctrl = OGL_CreateController(5.0f, 0.1f);
    ctrl->firstMouse = 1;
    
    /* Camera setup */
    glm::vec3 camPos = glm::vec3(
        plane->position[0],
        plane->position[1] + 1.0f,
        plane->position[2]
    );
    glm::vec3 upVec = glm::vec3(0, 1, 0);
    float yaw = -90.0f;
    float pitch = 0.0f;
    
    OGL_Camera* cam = OGL_CreateCamera(camPos, upVec, yaw, pitch);
    
    /* Bind camera to controller */
    OGL_BindCameraToController(ctrl, cam);
    
    /* Bind controller keys */
    OGL_BindControllerWASD(ctrl);
    
    /* Graphics pipeline for the shader program */
    GLuint TRS_MVP_Shader;
    TRS_MVP_Shader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_TextureV, OGLS_TRS_MVP_TextureF);

    /* Some otehr shader */
    GLuint TRS_MVP_Color_Shader;
    TRS_MVP_Color_Shader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_ColorV, OGLS_TRS_MVP_ColorF);
    
    /* Uniforms to send */
    float uPlaneColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float uCubeColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    /* Main loop, and timing */
    Uint32 lastTime = SDL_GetTicks();
    float dt = 0.0f;

    bool SDL2_Quit = false;
    while(!SDL2_Quit){
        OGL_SetScreenBackground(1.f, 1.f, 0.f, 1.f);

        Uint32 now = SDL_GetTicks();
        dt = (now - lastTime) / 1000.0f; /* Convert to seconds */
        lastTime = now;

        /* Same in each camera always */
        glm::mat4 view = OGL_GetViewMatrix(cam);
        glm::mat4 proj = OGL_GetProjMatrix(cam);

        /* Updates to assets / sprites / objects in general */
        SDL2_HandleEvents(SDL2_Quit, ctrl); /* Creates a new event to poll per call (Might need to be optimised) */

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        OGL_HandleControllerKeyboard(ctrl, keys, dt);
        
        /* Rendering order matters */
        /* Need to pass each uniform before drawing */

        /* --------------------- PLANE OBJECT --------------------- */
        OGL_PreDraw(TRS_MVP_Color_Shader);

        /* Send model TRS */
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uTrans"),     1, plane->position);
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uRotate"),    1, plane->rotation);
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uScale"),     1, plane->scale);

        /* Send camera matrices */
        glUniformMatrix4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uView"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uProj"), 1, GL_FALSE, glm::value_ptr(proj));

        /* Send color */
        glUniform4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uColor"), 1, uPlaneColor);

        OGL_DrawObject(plane->mesh);

        /* --------------------- OTHER OBJECT --------------------- */
        OGL_PreDraw(TRS_MVP_Color_Shader); /* Shader to use for the object */

        /* Rotation */
        obj->rotation[1] += 0.2;

        /* Send model TRS */
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uTrans"),     1, obj->position);
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uRotate"),    1, obj->rotation);
        glUniform3fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uScale"),     1, obj->scale);

        /* Send camera matrices */
        glUniformMatrix4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uView"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uProj"), 1, GL_FALSE, glm::value_ptr(proj));

        /* Send color */
        glUniform4fv(glGetUniformLocation(TRS_MVP_Color_Shader, "uColor"), 1, uCubeColor);

        OGL_DrawObject(obj->mesh);

        /* Swap frame buffers */
        SDL_GL_SwapWindow(SDL2_Win);
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
