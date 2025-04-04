#include "OGL_InitContext.hpp"

SDL_GLContext OGL_Context = NULL;

void OGL_InitContext(SDL_Window* window){
    /* We first set the attributes, then we create the context */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); /* OpenGL 4.1 */
    /* Remove deprecated OpenGL functions, forces us to use the new ones */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); /* OpenGL 4.1 Core */

    /* Double buffer for smoother transitions */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    OGL_Context = SDL_GL_CreateContext(window);
    if(OGL_Context == NULL){
        std::fprintf(stderr, "OpenGL context couldn't be initialised %s\n", SDL_GetError());
        return;
    }

    /* Initialises the OpenGL functions by getting their addresses from the GPU */
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::fprintf(stderr, "GLAD was not initialised\n");
        return;
    }

    return;
}

void OGL_OpenGLInfo(void){
    std::fprintf(stdout, "Vendor: %s\n", glGetString(GL_VENDOR));
    std::fprintf(stdout, "Renderer: %s\n", glGetString(GL_RENDERER));
    std::fprintf(stdout, "Version: %s\n", glGetString(GL_VERSION));
    std::fprintf(stdout, "Shader Lang: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
