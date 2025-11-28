#include "OGL_Controller.hpp"

OGL_Controller* OGL_NewController(float speed, float sensitivity) {
    OGL_Controller* newController = new OGL_Controller;

    newController->sensitivity = sensitivity;
    newController->speed = speed;

    return newController;
}

void OGL_BindCameraToController(OGL_Controller* control, OGL_Camera* cam){
    control->cam = cam;
}

void OGL_BindControllerForward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerBackward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerLeftward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerRightward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerUpward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerDownward(OGL_Controller* control, SDL_Scancode s);

void OGL_BindControllerArrowKeys(OGL_Controller* control);

void OGL_BindControllerWASD(OGL_Controller* control);

void OGL_BindControllerWASDShiftSpace(OGL_Controller* control);
