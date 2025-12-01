#include "OGL_Controller.hpp"

OGL_Controller* OGL_CreateController(float speed, float sensitivity) {
    OGL_Controller* newController = new OGL_Controller;

    newController->sensitivity = sensitivity;
    newController->speed = speed;

    /* Nullify the scancodes at first */
    newController->forwardScancode = new SDL_Scancode;
    newController->backwardScancode = new SDL_Scancode;
    newController->leftwardScancode = new SDL_Scancode;
    newController->rightwardScancode = new SDL_Scancode;
    newController->upwardScancode = new SDL_Scancode;
    newController->downwardScancode = new SDL_Scancode;

    newController->firstMouse = 1;
    newController->lastX = 0.0f;
    newController->lastY = 0.0f;

    return newController;
}

void OGL_BindCameraToController(OGL_Controller* control, OGL_Camera* cam){
    control->cam = cam;
}

void OGL_BindControllerForward(OGL_Controller* control, SDL_Scancode s){
    *control->forwardScancode = s;
    
    return;    
}

void OGL_BindControllerBackward(OGL_Controller* control, SDL_Scancode s){
    *control->backwardScancode = s;
    
    return;    
}

void OGL_BindControllerLeftward(OGL_Controller* control, SDL_Scancode s){
    *control->leftwardScancode = s;
    
    return;    
}

void OGL_BindControllerRightward(OGL_Controller* control, SDL_Scancode s){
    *control->rightwardScancode = s;
        
    return;    
}

void OGL_BindControllerUpward(OGL_Controller* control, SDL_Scancode s){
    *control->upwardScancode = s;

    return;    
}

void OGL_BindControllerDownward(OGL_Controller* control, SDL_Scancode s){
    *control->upwardScancode = s;

    return;    
}

void OGL_BindControllerArrowKeys(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_LEFT);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_RIGHT);
    OGL_BindControllerForward(control, SDL_SCANCODE_UP);
    OGL_BindControllerBackward(control, SDL_SCANCODE_DOWN);

    return;    
}

void OGL_BindControllerWASD(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_A);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_D);
    OGL_BindControllerForward(control, SDL_SCANCODE_W);
    OGL_BindControllerBackward(control, SDL_SCANCODE_S);
    
    return;    
}

/* Default bindings, WASD keys */
#define OGL_BindControllerDefault(control) OGL_BindControllerWASD(control)

void OGL_BindControllerWASDShiftSpace(OGL_Controller* control){
    // TODO    
    
    return;
}

void OGL_HandleControllerKeyboard(OGL_Controller* control, const Uint8* keyState, float dt){
    OGL_Camera* cam = control->cam;
    float velocity = control->speed * dt;
    
    if(control->forwardScancode){
        if(keyState[*control->forwardScancode]){
            cam->pos += cam->front * velocity;            
        }
    }
    
    if(control->backwardScancode){
        if(keyState[*control->backwardScancode]){
            cam->pos -= cam->front * velocity;            
        }
    }
    
    if(control->leftwardScancode){
        if(keyState[*control->leftwardScancode]){
            cam->pos -= cam->right * velocity;            
        }
    }

    if(control->rightwardScancode){
        if(keyState[*control->rightwardScancode]){
            cam->pos += cam->right * velocity;            
        }
    }
    
    if(control->upwardScancode){
        if(keyState[*control->upwardScancode]){
            // TODO
        }
    }
    
    if(control->downwardScancode){
        if(keyState[*control->downwardScancode]){
            // TODO        
        }
    }

    return;        
}

void OGL_HandleControllerMouse(OGL_Controller* control, float xRel, float yRel){
    OGL_Camera* cam = control->cam;
    
    float xOff = xRel * control->sensitivity;
    float yOff = yRel * control->sensitivity;

    cam->yaw -= xOff;
    cam->pitch -= yOff;

    /* Prevent camera flipping */
    // if(cam->pitch > 89.0f) cam->pitch = 89.0f;
    // if(cam->pitch < -89.0f) cam->pitch = -89.0f;

    OGL_UpdateCamera(cam);
    
    return;   
}
