#pragma once

#include "OGL_Camera.hpp"

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

typedef struct OGL_Controller{
    OGL_Camera* cam;                     /* Controller camera */
    
    float speed;                         /* Controller speed */
    float sensitivity;                   /* Controller mouse sensitivity */

    SDL_Scancode* forwardScancode;       /* Scancode for forward movement */
    SDL_Scancode* backwardScancode;      /* Scancode for backward movement */
    SDL_Scancode* leftwardScancode;      /* Scancode for leftward movement */
    SDL_Scancode* rightwardScancode;     /* Scancode for rightward movement */
    SDL_Scancode* upwardScancode;        /* Scancode for upward movement */
    SDL_Scancode* downwardScancode;      /* Scancode for downward movement */

    int mouse = 1;                       /* Mouse has an effect in the camera's view when moving */
    int mouseZoom = 0;                   /* Mouse has an effect in the camera's 'z' when scrolling */

    int firstMouse;                      /* Flag to avoid sudden mouse jumps on input */
    float lastX;                         /* Last mouse screen X */
    float lastY;                         /* Last mouse screen Y */
}OGL_Controller;

/**
 * @brief Create a new controller object
 * 
 * @param speed Controller movement speed
 * @param sensitivity Contoller mouse sensitivity
 * 
 * @returns The new controller object
 */
OGL_Controller* OGL_CreateController(float speed, float sensitivity);

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
 * @brief Bind controller movement to the arrow keys (3D)
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerArrowKeys3D(OGL_Controller* control);

/**
 * @brief Bind controller movement to the WASD keys (3D)
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerWASD3D(OGL_Controller* control);

/**
 * @brief Bind controller movement to the arrow keys (2D)
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerArrowKeys2D(OGL_Controller* control);

/**
 * @brief Bind controller movement to the WASD keys (2D)
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerWASD2D(OGL_Controller* control);

/**
 * @brief Bind controller movement to the WASD/Space/Shift keys (3D)
 * 
 * @param control Controller to bind
 */
void OGL_BindControllerWASDShiftSpace3D(OGL_Controller* control);

/**
 * @brief Handle controller's keyboard input 
 *
 * @param control Controller to handle
 * @param keyState State of pressed keys
 * @param dt Time delta to apply speeds
 */
void OGL_HandleControllerKeyboard(OGL_Controller* control, const Uint8* keyState, float dt);

/**
 * @brief Handle controller's mouse movement
 *
 * @param control Controller to handle 
 * @param xRel Relative mouse x coordinate
 * @param yRel Relative mouse y coordinate
 */
void OGL_HandleControllerMouse(OGL_Controller* control, float xRel, float yRel);

