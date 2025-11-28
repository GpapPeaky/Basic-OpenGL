#pragma once

#include "OGL_Camera.hpp"
#include "OGL_Scancode.hpp"

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

typedef struct OGL_Controller{
    OGL_Camera* cam;                    /* Controller camera */
    float speed;                        /* Controller speed */
    float sensitivity;                  /* Controller mouse sensitivity */

    SDL_Scancode forwardScanode;        /* Scancode for forward movement */
    SDL_Scancode backwardScancode;      /* Scancode for backward movement */
    SDL_Scancode leftwardScancode;      /* Scancode for leftward movement */
    SDL_Scancode rightwadScancode;      /* Scancode for rightward movement */
    SDL_Scancode upwardScancode;        /* Scancode for upward movement */
    SDL_Scancode downwardScancode;      /* Scancode for downward movement */
}OGL_Controller;

/**
 * @brief Create a new controller object
 * 
 * @param speed Controller movement speed
 * @param sensitivity Contoller mouse sensitivity
 * 
 * @returns The new controller object
 */
OGL_Controller* OGL_NewController(float speed, float sensitivity);

/**
 * @brief Bind a camera to a controller
 * 
 * @param control Controller
 * @param cam Camera to bind
 */
void OGL_BindCameraToController(OGL_Controller* control, OGL_Camera* cam);

/**
 * @brief Bind forward movement to a scancode
 * 
 * @param control Controller to bind forward
 * @param s Scancode to bind
 */
void OGL_BindControllerForward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind backward movement to a scancode
 * 
 * @param control Controller to bind backward
 * @param s Scancode to bind
 */
void OGL_BindControllerBackward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind leftward movement to a scancode
 * 
 * @param control Controller to bind leftward
 * @param s Scancode to bind
 */
void OGL_BindControllerLeftward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind rightward movement to a scancode
 * 
 * @param control Controller to bind rightward
 * @param s Scancode to bind
 */
void OGL_BindControllerRightward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind upward movement to a scancode
 * 
 * @param control Controller to bind upward
 * @param s Scancode to bind
 */
void OGL_BindControllerUpward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind down movement to a scancode
 * 
 * @param control Controller to bind down
 * @param s Scancode to bind
 */
void OGL_BindControllerDownward(OGL_Controller* control, SDL_Scancode s);

/**
 * @brief Bind controller movement to the arrow keys
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerArrowKeys(OGL_Controller* control);

/**
 * @brief Bind controller movement to the WASD keys
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerWASD(OGL_Controller* control);

/**
 * @brief Bind controller movement to the WASD/Space/Shift keys
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerWASDShiftSpace(OGL_Controller* control);
