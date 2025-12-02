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
    plane->position[0] = 0.f; plane->position[1] = 0.0f; plane->position[2] = 0.f;
    plane->rotation[0] = 0.f; plane->rotation[1] = 45.0f; plane->rotation[2] = 0.f;
    plane->scale[0]    = 10.f; plane->scale[1]    = 0.1f; plane->scale[2]    = 10.f;
    
    /* Objects creation */
    GLuint TRS_MVP_TextureShader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_TextureV, OGLS_TRS_MVP_TextureF);

    OGL_Object* obj1 = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectT(*obj1->mesh);
    OGL_LoadBitmapToObject(*obj1->mesh, "assets/a3.bmp");
    obj1->scale[0]    = 1.f; obj1->scale[1]    = 12.f; obj1->scale[2]    = 1.f;
    obj1->rotation[0] = 0.f; obj1->rotation[1] = 0.f; obj1->rotation[2] = 0.f;
    obj1->position[0] = 0.f; obj1->position[1] = obj1->scale[1] / 2; obj1->position[2] = 0.f;

    OGL_Object* obj2 = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectT(*obj2->mesh);
    OGL_LoadBitmapToObject(*obj2->mesh, "assets/a3.bmp");
    obj2->position[0] = 3.f; obj2->position[1] = 0.f; obj2->position[2] = 0.f;
    obj2->rotation[0] = 0.f; obj2->rotation[1] = 0.f; obj2->rotation[2] = 0.f;
    obj2->scale[0]    = 1.f; obj2->scale[1]    = 1.f; obj2->scale[2]    = 0.02f;

    OGL_Object* obj3 = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectT(*obj3->mesh);
    OGL_LoadBitmapToObject(*obj3->mesh, "assets/a3.bmp");
    obj3->position[0] = 2.f; obj3->position[1] = 0.f; obj3->position[2] = 3.f;
    obj3->rotation[0] = 0.f; obj3->rotation[1] = 0.f; obj3->rotation[2] = 0.f;
    obj3->scale[0]    = 1.f; obj3->scale[1]    = 1.f; obj3->scale[2]    = 0.02f;
    
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
        obj2->rotation[1] += 0.3;
        obj3->rotation[1] -= 0.2;
        obj3->position[1] = cosf(theta) * 0.5;
        theta += 0.01f;

        OGL_SetScreenBackground(0.f, 0.3f, 0.95f, 1.f);

        OGL_Render(obj1);
        OGL_Render(obj2);
        OGL_Render(obj3);
        OGL_Render(plane);

        /* Swap frame buffers */
        SDL_GL_SwapWindow(SDL2_Win);

        /* Frame limiter to 120 FPS */
        Uint32 frameTime = SDL_GetTicks() - now;
        if(frameTime < 1000 / 120){
            SDL_Delay(1000 / 120 - frameTime);
        }
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
