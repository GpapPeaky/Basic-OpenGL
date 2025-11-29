#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);

    OGL_VertexObject obj;

    // OGL_CreateTextureQuad(bmp);
    // OGL_LoadBitmapToObject(bmp, "assets/pn003.bmp");

    OGL_CreateCubeVertexObject(obj);

    /* Controller creation */
    OGL_Controller* ctrl = OGL_CreateController(5.0f, 1.0f);
    
    /* Camera setup */
    glm::vec3 camPos = glm::vec3(0, 0, 3);
    glm::vec3 upVec = glm::vec3(0, 1, 0);
    float yaw = -90.0f;
    float pitch = 0.0f;
    
    OGL_Camera* cam = OGL_CreateCamera(camPos, upVec, yaw, pitch);
    
    /* Bind camera to controller */
    OGL_BindCameraToController(ctrl, cam);
    
    /* Bind controller keys */
    OGL_BindControllerWASD(ctrl);
    
    /* Graphics pipeline for the shader program */
    GLuint s1;
    s1 = OGL_CreateGraphicsPipeline(OGLS_PeakyV, OGLS_PeakyF);
    
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
    
        /* OpenGL rendering functions */
        OGL_SetScreenBackground(1.f, 1.f, 0.f, 1.f);
        
        /* Rendering order matters */
        OGL_PreDraw(s1); /* Shader to use */
        OGL_DrawObject(obj);

        /* Swap frame buffers */
        SDL_GL_SwapWindow(SDL2_Win);
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
