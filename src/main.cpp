#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);
    
    /* Lightweight root object */
    OGL_Shader rootObject_Shader = OGL_CreateGraphicsPipeline(OGLS_ROOT_OBJ_V, OGLS_ROOT_OBJ_F);
    OGL_Object* rootObj = OGL_CreateObject(rootObject_Shader);
    OGL_Scene = OGL_CreateNode(rootObj, "root");
    
    /* Objects creation */

    /* This shader requires a material */
    OGL_Shader TRS_MVP_TextureShader = OGL_CreateGraphicsPipeline(
        OGLS_TRS_MVP_TextureV,
        OGLS_TRS_MVP_TextureF
    );

    float lightColors[3] = { 1.0f, 1.0f, 1.0f };
    float emitColors[3] = { 0.0f, 0.0f, 0.0f };
    OGL_Material mat1 = OGL_CreateMaterial(
        lightColors,
        lightColors,
        lightColors,
        0.02f,
        emitColors,
        0.0f
    );

    OGL_Material mat2 = OGL_CreateMaterial(
        emitColors,
        emitColors,
        emitColors,
        0.02f,
        emitColors,
        0.0f
    );

    /* Plane creation*/
    // OGL_Shader TRS_MVP_Color_Shader = OGL_CreateGraphicsPipeline(OGLS_TRS_MVP_ColorV, OGLS_TRS_MVP_ColorF);
    OGL_Object* plane = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectFC(*plane->mesh);
    OGL_AssignMaterialToObject(plane, mat2);
    OGL_LoadBitmapToObject(*plane->mesh, "assets/a1.bmp");
    OGL_AssignColorToObject(plane, 0.1f, 0.4f, 0.0f, 1.0f);
    plane->position[0] = 0.f; plane->position[1] = 0.0f; plane->position[2] = 0.f;
    plane->rotation[0] = 0.f; plane->rotation[1] = 0.0f; plane->rotation[2] = 0.f;
    plane->scale[0]    = 10.f; plane->scale[1]   = 10.f; plane->scale[2]    = 10.f;
    /* Create the object node */
    OGL_ONode* onodePlane = OGL_CreateNode(plane, "plane");

    OGL_Object* obj1 = OGL_CreateObject(TRS_MVP_TextureShader);
    OGL_CreateCubeVertexObjectT(*obj1->mesh);
    OGL_LoadBitmapToObject(*obj1->mesh, "assets/a3.bmp");
    OGL_AssignMaterialToObject(obj1, mat1);
    obj1->scale[0]    = 1.f; obj1->scale[1]    = 1.f; obj1->scale[2]    = 0.05f;
    obj1->rotation[0] = 0.f; obj1->rotation[1] = 180.f; obj1->rotation[2] = 0.f;
    obj1->position[0] = 0.f; obj1->position[1] = obj1->scale[1] / 2; obj1->position[2] = 5.f;
    OGL_ONode* onode1 = OGL_CreateNode(obj1, "obj1");
    
    /* Hierarchy */
    OGL_AttachChild(OGL_Scene, onodePlane);
    OGL_AttachChild(OGL_Scene, onode1);
    
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
    OGL_BindControllerWASD2D(ctrl);

    /* Miscellanious */
    float theta = 0.5f; /* Rotation */
    float radius = 5.0f;
    float speed  = 0.5f;

    /* Main loop, and timing */
    Uint32 lastTime = SDL_GetTicks();
    float dt = 0.0f;

    // onode1->active = false;

    bool SDL2_Quit = false;
    while(!SDL2_Quit){
        Uint32 now = SDL_GetTicks();
        dt = (now - lastTime) / 1000.0f; /* Convert to seconds */
        lastTime = now;

        /* Updates to assets / sprites / objects in general */
        SDL2_HandleEvents(SDL2_Quit, ctrl); /* Creates a new event to poll per call (Might need to be optimised) */
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        OGL_HandleControllerKeyboard(ctrl, keys, dt);
        
        /* Rendering order matters */
        /* Need to pass each uniform before drawing */
        
        /* Updates */
        onode1->o->rotation[1] += theta;
        theta += dt * speed;  // accumulate angle over time

        onode1->o->position[0] = radius * cos(theta);
        onode1->o->position[2] = radius * sin(theta);

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
