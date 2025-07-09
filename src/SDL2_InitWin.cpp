#include "SDL2_InitWin.hpp"

SDL_Window* SDL2_Win;
SDL_Renderer* SDL2_Rnd;
Uint32 SDL2_WinWidth;
Uint32 SDL2_WinHeight;
float SDL2_AspectRatio;

int SDL2_InitWin(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::fprintf(stderr, "OGL_SDL2_ERR: SDL could not initialise: %s\n",SDL_GetError());
        return FAILURE;
    }

    /* Initialising window and renderer */
    SDL2_Win = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 432, 500, SDL_WINDOW_OPENGL);
    if(SDL2_Win == NULL){
        std::fprintf(stderr, "OGL_SDL2_ERR: Failed to create window: %s\n", SDL_GetError());
        return FAILURE;
    }

    /* Have this globally saved, since it is useful */
    SDL_GetWindowSize(SDL2_Win, (int*)&SDL2_WinWidth, (int*)&SDL2_WinHeight);

    if(SDL2_WinHeight != 0){
        SDL2_AspectRatio = (float)SDL2_WinWidth / (float)SDL2_WinHeight;
    }else{
        SDL2_AspectRatio = 1.0f;
    }

    SDL2_Rnd = SDL_CreateRenderer(SDL2_Win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(SDL2_Rnd == NULL){
        std::fprintf(stderr, "OGL_SDL2_ERR: Failed to create renderer: %s\n", SDL_GetError());
        return FAILURE;
    }

    std::printf("Window Size: %ux%u, Aspect Ratio: %f\n", SDL2_WinWidth, SDL2_WinHeight, SDL2_AspectRatio);

    return SUCCESS;
}
