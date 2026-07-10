#include "auxf/includes.aux"

int main(int, char**){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);

    OGL_InitShaderRegistry();

    /* Controller creation */
    OGL_Controller* ctrl = OGL_CreateController(5.0f, 0.1f);

    /* Camera setup */
    OGL_Camera* cam = OGL_CreateCamera({0.0f, 0.0f, 10.0f}, {0, 1, 0}, 0.0f, 0.0f);
    
    /* Bind camera to controller */
    OGL_BindCameraToController(ctrl, cam);
    
    /* Bind a camera to the render view */
    OGL_BindCameraToRenderView(cam);
    
    /* Bind controller keys */
    OGL_BindControllerWASD2D(ctrl);
    
    /* Lightweight root object */
    OGL_Object* rootObj = OGL_CreateObject(OGL_GetShader("rootobj"));
    OGL_Scene = OGL_CreateNode(rootObj, "root");
    
    /* Plane creation */
    OGL_Object* plane = OGL_CreateObject(OGL_GetShader("color"));
    OGL_CreateCubeVertexObjectFC(*plane->mesh);
    OGL_AssignColorToObject(plane, 1.0f, 0.0f, 0.0f, 1.0f);
    /* Create the object node */
    OGL_ONode* onodePlane = OGL_CreateNode(plane, "plane");
    /* Hierarchy */
    OGL_AttachChild(OGL_Scene, onodePlane);

    /* Main loop, and timing */
    Uint32 lastTime = SDL_GetTicks();
    float dt = 0.0f;

    bool OGL_GameQuit = false;
    while(!OGL_GameQuit){
        Uint32 now = SDL_GetTicks();
        dt = (now - lastTime) / 1000.0f; /* Convert to seconds */
        lastTime = now;

        /* Updates to assets / sprites / objects in general */
        SDL2_HandleEvents(OGL_GameQuit, ctrl); /* Creates a new event to poll per call (Might need to be optimised) */
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        OGL_HandleControllerKeyboard(ctrl, keys, dt);
        
        /* Rendering order matters */
        /* Need to pass each uniform before drawing */
        
        /* Updates */

        OGL_SetScreenBackground(0.f, 0.3f, 0.95f, 1.f);

        OGL_RenderVisitChildren(OGL_Scene);
    
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
