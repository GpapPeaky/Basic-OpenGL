#include "OGL_Controller.hpp"

OGL_Controller* OGL_CreateController(float speed, float sensitivity) {
    OGL_Controller* newController = new OGL_Controller{};

    newController->sensitivity = sensitivity;
    newController->speed = speed;

    /* Nullify the scancodes at first */
    newController->forwardScancode = NULL;
    newController->backwardScancode = NULL;
    newController->leftwardScancode = NULL;
    newController->rightwardScancode = NULL;
    newController->upwardScancode = NULL;
    newController->downwardScancode = NULL;

    newController->firstMouse = 1;
    newController->lastX = 0.0f;
    newController->lastY = 0.0f;

    return newController;
}

void OGL_BindCameraToController(OGL_Controller* control, OGL_Camera* cam){
    control->cam = cam;
}

void OGL_BindControllerForward(OGL_Controller* control, SDL_Scancode s){
    control->forwardScancode = new SDL_Scancode;
    *control->forwardScancode = s;
    
    return;    
}

void OGL_BindControllerBackward(OGL_Controller* control, SDL_Scancode s){
    control->backwardScancode = new SDL_Scancode;
    *control->backwardScancode = s;
    
    return;    
}

void OGL_BindControllerLeftward(OGL_Controller* control, SDL_Scancode s){
    control->leftwardScancode = new SDL_Scancode;
    *control->leftwardScancode = s;
    
    return;    
}

void OGL_BindControllerRightward(OGL_Controller* control, SDL_Scancode s){
    control->rightwardScancode = new SDL_Scancode;
    *control->rightwardScancode = s;
        
    return;    
}

void OGL_BindControllerUpward(OGL_Controller* control, SDL_Scancode s){
    control->upwardScancode = new SDL_Scancode;
    *control->upwardScancode = s;

    return;    
}

void OGL_BindControllerDownward(OGL_Controller* control, SDL_Scancode s){
    control->downwardScancode = new SDL_Scancode;
    *control->downwardScancode = s;

    return;    
}

void OGL_BindControllerArrowKeys3D(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_LEFT);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_RIGHT);
    OGL_BindControllerForward(control, SDL_SCANCODE_UP);
    OGL_BindControllerBackward(control, SDL_SCANCODE_DOWN);

    return;    
}

void OGL_BindControllerWASD3D(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_A);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_D);
    OGL_BindControllerForward(control, SDL_SCANCODE_W);
    OGL_BindControllerBackward(control, SDL_SCANCODE_S);
    
    return;    
}

void OGL_BindControllerWASD2D(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_A);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_D);
    OGL_BindControllerUpward(control, SDL_SCANCODE_W);
    OGL_BindControllerDownward(control, SDL_SCANCODE_S);

    control->mouse = false;

    return;
}

void OGL_BindControllerArrowKeys2D(OGL_Controller* control){
    OGL_BindControllerLeftward(control, SDL_SCANCODE_LEFT);    
    OGL_BindControllerRightward(control, SDL_SCANCODE_RIGHT);
    OGL_BindControllerUpward(control, SDL_SCANCODE_UP);
    OGL_BindControllerDownward(control, SDL_SCANCODE_DOWN);

    control->mouse = false;

    return;
}

/* Default bindings, WASD keys for 3D space movemment */
#define OGL_BindControllerDefault3D(control) OGL_BindControllerWASD3D(control)

/* Default bindings, WASD keys for 2D plane movement */
#define OGL_BindControllerDefault2D(control) OGL_BindControllerWASD2D(control)

void OGL_BindControllerWASDShiftSpace(OGL_Controller* control){
    OGL_BindControllerWASD3D(control);
    OGL_BindControllerUpward(control, SDL_SCANCODE_SPACE);    
    OGL_BindControllerDownward(control, SDL_SCANCODE_LSHIFT);    
    
    return;
}

void OGL_HandleControllerKeyboard(OGL_Controller* control, const Uint8* keyState, float dt){
    if (!control || !control->cam || !keyState) {
        std::fprintf(stderr, "OGL_ERR: Invalid controller state\n");
        return;
    }

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
            cam->pos += cam->up * velocity;
        }
    }
    
    if(control->downwardScancode){
        if(keyState[*control->downwardScancode]){
            cam->pos -= cam->up * velocity;
        }
    }

    return;        
}

void OGL_HandleControllerMouse(OGL_Controller* control, float xRel, float yRel){
    OGL_Camera* cam = control->cam;
    
    float xOff = xRel * control->sensitivity;
    float yOff = yRel * control->sensitivity;

    if(control->mouse){
        cam->yaw    -= xOff;
        cam->pitch  -= yOff;
    }

    /* Prevent camera flipping */
    // if(cam->pitch > 89.0f) cam->pitch = 89.0f;
    // if(cam->pitch < -89.0f) cam->pitch = -89.0f;

    OGL_UpdateCamera(cam);
    
    return;   
}
