#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    /* Initialise SDL2 and OpenGL */
    SDL2_InitWin();
    OGL_InitContext(SDL2_Win);

    OGL_VertexObject bmp;

    OGL_CreateTextureQuad(bmp);
    OGL_LoadBitmapToObject(bmp, "assets/pn003.bmp");

    /* Graphics pipeline for the shader program */
    GLuint s1;
    s1 = OGL_CreateGraphicsPipeline(OGLS_TextureV, OGLS_TextureF);
    
    /* Main loop */
    bool SDL2_Quit = false;
    while(!SDL2_Quit){
        SDL2_HandleEvents(SDL2_Quit); /* Creates a new event to poll per call (Might need to be optimised) */

        /* Updates to assets / sprites / objects in general */

        /* OpenGL rendering functions */
        OGL_SetScreenBackground(1.f, 1.f, 0.f, 1.f);

        /* Rendering order matters */
        OGL_PreDraw(s1);
        OGL_DrawObject(bmp);

        SDL_GL_SwapWindow(SDL2_Win);
    }

    /* Cleanup */
    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    SDL_Quit();

    return SUCCESS;
}
