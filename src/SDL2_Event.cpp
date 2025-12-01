#include "SDL2_Event.hpp"

void SDL2_HandleEvents(bool& quit, OGL_Controller* ctrl){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_e))){
            quit = true;
        }
            

        /* Mouse movement */
        if(e.type == SDL_MOUSEMOTION){
            /* Compute change through raw input */
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            if(ctrl->firstMouse){
                ctrl->lastX = mouseX;
                ctrl->lastY = mouseY;
                ctrl->firstMouse = false;
                return;
            }
            
            float xRel = mouseX - ctrl->lastX;
            float yRel = mouseY - ctrl->lastY;
            
            ctrl->lastX = mouseX;
            ctrl->lastY = mouseY;
            
            OGL_HandleControllerMouse(ctrl, xRel, yRel);
        }
    }

    return;
}
