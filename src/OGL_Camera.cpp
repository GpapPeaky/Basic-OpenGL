#include "OGL_Camera.hpp"

OGL_Camera* OGL_CreateCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch){
    OGL_Camera* newCam = new OGL_Camera;
    
    newCam->pos = pos;
    newCam->worldUp = up;
    newCam->yaw = yaw;
    newCam->pitch = pitch;
    newCam->front = glm::vec3(0.0f, 0.0f, -1.0f);

    OGL_UpdateCamera(newCam);

    return newCam;
}

glm::mat4 OGL_GetViewMatrix(OGL_Camera* cam){
    return glm::lookAt(cam->pos, cam->pos + cam->front, cam->up);
}

void OGL_UpdateCamera(OGL_Camera* cam){
    glm::vec3 front;
    front.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    front.y = sin(glm::radians(cam->pitch));
    front.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));

    cam->front = glm::normalize(front);
    cam->right = glm::normalize(glm::cross(cam->front, cam->worldUp));
    cam->up    = glm::normalize(glm::cross(cam->right, cam->front));
}
