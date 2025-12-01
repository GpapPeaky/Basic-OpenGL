#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);

    /* Plane creation*/
    GLuint TRS_MVP_Color_Shader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_ColorV, OGLS_TRS_MVP_ColorF);
    OGL_Object* plane = OGL_CreateObject(TRS_MVP_Color_Shader);
    OGL_CreateCubeVertexObjectFC(*plane->mesh);
    OGL_AssignColorToObject(plane, 0.1f, 0.4f, 0.0f, 1.0f);
    plane->position[0] = 0.f; plane->position[1] = -0.6f; plane->position[2] = 0.f;
    plane->rotation[0] = 0.f; plane->rotation[1] = -0.6f; plane->rotation[2] = 0.f;
    plane->scale[0]    = 10.f; plane->scale[1]    = 0.1f; plane->scale[2]    = 10.f;
    
    /* Obj creation */
    GLuint TRS_MVP_TextureShader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_TextureV, OGLS_TRS_MVP_TextureF);
    OGL_Object* obj = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectT(*obj->mesh);
    OGL_LoadBitmapToObject(*obj->mesh, "assets/a2.bmp");
    obj->position[0] = 0.f; obj->position[1] = 0.f; obj->position[2] = 0.f;
    obj->rotation[0] = 0.f; obj->rotation[1] = 0.f; obj->rotation[2] = 0.f;
    obj->scale[0]    = 1.f; obj->scale[1]    = 1.f; obj->scale[2]    = 0.02f;
    
    /* Controller creation */
    OGL_Controller* ctrl = OGL_CreateController(5.0f, 0.1f);

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
    
    /* Bind a camera to the render view */
    OGL_BindCameraToRenderView(cam);
    
    /* Bind controller keys */
    OGL_BindControllerWASD(ctrl);

    /* Miscellanious */

    float theta = 0; /* Rotation */
    
    /* Main loop, and timing */
    Uint32 lastTime = SDL_GetTicks();
    float dt = 0.0f;

    bool SDL2_Quit = false;
    while(!SDL2_Quit){
        OGL_SetScreenBackground(1.f, 1.f, 0.f, 1.f);

        Uint32 now = SDL_GetTicks();
        dt = (now - lastTime) / 1000.0f; /* Convert to seconds */
        lastTime = now;

        /* Updates to assets / sprites / objects in general */
        SDL2_HandleEvents(SDL2_Quit, ctrl); /* Creates a new event to poll per call (Might need to be optimised) */

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        OGL_HandleControllerKeyboard(ctrl, keys, dt);
        
        /* Rendering order matters */
        /* Need to pass each uniform before drawing */

        /* Updates */
        obj->rotation[1] += 0.2;
        obj->position[1] = cosf(theta) * 0.5;
        theta += 0.01f;

        OGL_Render(obj);
        OGL_Render(plane);

        /* Swap frame buffers */
        SDL_GL_SwapWindow(SDL2_Win);
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
