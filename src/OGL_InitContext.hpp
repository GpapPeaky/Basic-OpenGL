#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../ThirdParty/GLAD/include/glad/glad.h" /* OpenGL */

#include "SDL2_InitWin.hpp" /* For the window */

extern SDL_GLContext OGL_Context; /* Global OpenGL window context */

/**
 * @brief Initialises the OpenGL context for a window
 * 
 * @param window Window to set the context to
 */
void OGL_InitContext(SDL_Window* window);

/**
 * @brief Checks and prints for OpenGL
 */
void OGL_OpenGLInfo(void);
