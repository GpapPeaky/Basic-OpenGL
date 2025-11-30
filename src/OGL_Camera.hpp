#pragma once

#include "../ThirdParty/glm/glm.hpp"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"

#include "SDL2_InitWin.hpp" /* Window dimensions */

typedef enum OGL_CameraMovement{
    OGL_CAMERA_FORWARD,
    OGL_CAMERA_BACKWARD,
    OGL_CAMERA_LEFT,
    OGL_CAMERA_RIGHT
}OGL_CameraMovement;

typedef struct OGL_Camera{
    glm::vec3 pos;          /* Camera position */
    glm::vec3 front;        /* */
    glm::vec3 up;           /* */
    glm::vec3 right;        /* */
    glm::vec3 worldUp;      /* */

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

    float yaw;              /* Euler angles */
    float pitch;
}OGL_Camera;

/**
 * @brief Create a new camera
 * 
 * @param pos Camera position
 * @param up Camera up vector
 * @param yaw Camera yaw
 * @param pitch Camera pitch
 * 
 * @returns The new camera object
 */
OGL_Camera* OGL_CreateCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);

/**
 * @brief Get camera view matrix
 * 
 * @param cam Camera
 * 
 * @returns The camera's view matrix, need for vertex shader
 */
glm::mat4 OGL_GetViewMatrix(OGL_Camera* cam);

/**
 * @brief Get camera projection matrix
 * 
 * @param cam Camera
 * 
 * @returns The camera's prohection matrix
 */
glm::mat4 OGL_GetProjMatrix(OGL_Camera* cam);

/**
 * @brief Update the cameras matrices
 * 
 * @param cam Camera to update
 */
void OGL_UpdateCamera(OGL_Camera* cam);
