#include "OGL_Camera.hpp"

OGL_Camera* OGL_CreateCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch){
    OGL_Camera* newCam = new OGL_Camera;
    
    newCam->pos = pos;
    newCam->worldUp = up;
    newCam->yaw = yaw;
    newCam->pitch = pitch;
    newCam->front = glm::vec3(0.0f, 0.0f, -1.0f);

    newCam->fov = 45.0f;
    newCam->aspect = static_cast<float>(SDL2_WinWidth) / static_cast<float>(SDL2_WinHeight); // Better to update than to cache it
    newCam->nearPlane = 0.1f;
    newCam->farPlane = 100.0f;

    OGL_UpdateCamera(newCam);

    return newCam;
}

glm::mat4 OGL_GetViewMatrix(OGL_Camera* cam){
    return glm::lookAt(cam->pos, cam->pos + cam->front, cam->up);
}

glm::mat4 OGL_GetProjMatrix(OGL_Camera* cam){
    return glm::perspective(
        glm::radians(cam->fov),    // FOV in radians
        cam->aspect,               // aspect ratio
        cam->nearPlane,            // near clipping plane
        cam->farPlane              // far clipping plane
    );
}

void OGL_UpdateCamera(OGL_Camera* cam){
    // Create quaternions for yaw (around worldUp) and pitch (around camera's right)
    glm::quat qYaw   = glm::angleAxis(glm::radians(cam->yaw), cam->worldUp);
    
    // Compute current right vector for pitch rotation
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0,0,-1), cam->worldUp));
    glm::quat qPitch = glm::angleAxis(glm::radians(cam->pitch), right);

    glm::quat orientation = qYaw * qPitch;

    cam->front = glm::normalize(orientation * glm::vec3(0,0,-1));
    cam->right = glm::normalize(glm::cross(cam->front, cam->worldUp));
    cam->up    = glm::normalize(glm::cross(cam->right, cam->front));

    return;
}
