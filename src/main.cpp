#include "auxf/includes.aux"

int main(int, char**){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);
    OGL_InitShaderRegistry();
    
    unsigned int fontHeight = 45;
    FT_Library ft = OGL_InitFreeType();
    FT_Face fc = OGL_LoadFont(ft, "assets/fonts/Minecraft.ttf", fontHeight);
    std::map<char, OGL_Character> chars = OGL_LoadCharacters(fc);

    /* Controller creation */
    OGL_Controller* ctrl = OGL_CreateController(5.0f, 0.1f);

    /* Camera setup */
    OGL_Camera* cam = OGL_CreateCamera({0.0f, 0.0f, 50.0f}, {0, 1, 0}, 0.0f, 0.0f);
    
    /* Bind camera to controller */
    OGL_BindCameraToController(ctrl, cam);
    
    /* Bind a camera to the render view */
    OGL_BindCameraToRenderView(cam);
    
    /* Bind controller keys */
    OGL_BindControllerWASD3D(ctrl);
    
    /* Lightweight root object */
    OGL_Object* rootObj = OGL_CreateObject(OGL_GetShader("rootobj"));
    OGL_Scene = OGL_CreateNode(rootObj, "root");
    
    /* Plane creation */
    OGL_Object* plane = OGL_CreateObject(OGL_GetShader("tex"));
    OGL_CreateTextureQuad(*plane->mesh);
    OGL_LoadBitmapToObject(*plane, "assets/a2.bmp");
    /* Create the object node */
    OGL_ONode* onodePlane = OGL_CreateNode(plane, "plane");
    TRS::S(*plane, {10.0f * 2.035f, 10.f, 1.f});
    /* Hierarchy */
    OGL_AttachChild(OGL_Scene, onodePlane);

    /* Plane creation */
    OGL_Object* plane2 = OGL_CreateObject(OGL_GetShader("tex"));
    OGL_CreateTextureQuad(*plane2->mesh);
    OGL_LoadBitmapToObject(*plane2, "assets/a1.bmp");
    /* Create the object node */
    OGL_ONode* onodePlane2 = OGL_CreateNode(plane2, "plane2");
    TRS::T(*plane2, {15.f, 0.f, 5.f});
    TRS::R(*plane2, {0.f, -45.f, 0.f});
    TRS::S(*plane2, {10.f, 10.f, 1.f});
    /* Hierarchy */
    OGL_AttachChild(OGL_Scene, onodePlane2);

    /* No renderable content, if no OGL_RenderText is called with this object, nothing is rendered */
    OGL_Object* text = OGL_CreateObject(OGL_GetShader("glyph"));
    OGL_CreateTextQuad(*text->mesh);

    // OGL_AttachChild(OGL_Scene, onodeText); // Not attached to the scene

    /* Main loop, and timing */
    Uint32 lastTime = SDL_GetTicks();

    bool OGL_GameQuit = false;
    while(!OGL_GameQuit){
        Uint32 now = SDL_GetTicks();
        OGL_GameDt = (now - lastTime) / 1000.0f;            /* Convert to seconds */
        lastTime = now;

        /* Updates to assets / sprites / objects in general */
        SDL2_HandleEvents(OGL_GameQuit, ctrl);      /* Creates a new event to poll per call (Might need to be optimised) */
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        OGL_HandleControllerKeyboard(ctrl, keys, OGL_GameDt);
        
        /* Rendering order matters */
        /* Need to pass each uniform before drawing */
        
        /* Updates */

        OGL_SetScreenBackground(0.f, 0.3f, 0.95f, 1.f);

        OGL_RenderVisitChildren(OGL_Scene);

        /* Text has to be on top of whatever is rendered, else it gets culled */
        /* Text is rendered to screen coordinates, since we are using simple shaders along with glm::ortho (0, winwidth, 0, winheight) */

        OGL_RenderText(
            *text,
            "Exw balei to filo sou na mou stelnei gara",
            0.0f,     // baseline x
            (float)fontHeight,    // height
            1.0f,
            {1.0f, 1.0f, 1.0f},
            chars
        );
        OGL_RenderText(
            *text,
            "Poutana apo amerikh thn fonazoune sara",
            0.0f,     // baseline x
            (float)fontHeight * 2.0f,    // height
            1.0f,
            {1.0f, 1.0f, 1.0f},
            chars
        );
        
        /* Swap frame buffers */
        SDL_GL_SwapWindow(SDL2_Win);

        /* Accumulate time */
        OGL_GameTime += OGL_GameDt;
        /* Frame limiter to OGL_FrameLimit FPS */
        Uint32 frameTime = SDL_GetTicks() - now;
        if(frameTime < 1000 / OGL_FrameLimit){
            SDL_Delay(1000 / OGL_FrameLimit - frameTime);
        }
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
