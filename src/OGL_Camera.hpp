#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "../ThirdParty/glm/glm.hpp"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "../ThirdParty/glm/gtc/type_ptr.hpp"
#include "../ThirdParty/glm/gtc/quaternion.hpp"
#include "../ThirdParty/glm/gtx/quaternion.hpp"

#include "SDL2_InitWin.hpp" /* Window dimensions */

typedef enum OGL_CameraMovement{
    OGL_CAMERA_FORWARD,
    OGL_CAMERA_BACKWARD,
    OGL_CAMERA_LEFT,
    OGL_CAMERA_RIGHT
}OGL_CameraMovement;

typedef struct OGL_Camera{
    glm::vec3 pos       = {0.f, 0.f, 0.f};           /* Camera position */
    glm::vec3 front     = {0.f, 0.f, 0.f};           /* */
    glm::vec3 up        = {0.f, 0.f, 0.f};           /* */
    glm::vec3 right     = {0.f, 0.f, 0.f};           /* */
    glm::vec3 worldUp   = {0.f, 0.f, 0.f};           /* */

    float fov = 0.0f;
    float aspect = 0.0f;
    float nearPlane = 0.0f;
    float farPlane = 0.0f;

    float yaw = 0.0f;              /* Euler angles */
    float pitch = 0.0f;

    float zoom = 0.0f;
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
