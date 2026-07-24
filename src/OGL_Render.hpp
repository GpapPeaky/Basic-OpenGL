#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../ThirdParty/GLAD/include/glad/glad.h"

#include "SDL2_InitWin.hpp"      // For creating the shader object to be used in the graphics pipeline

#include "OGL_Shader.hpp"        // For creating the shader object to be used in the graphics pipeline
#include "OGL_Object.hpp"        // For the vertex object abstraction
#include "OGL_ObjectNode.hpp"    // For rendering objects with hierarchy
#include "OGL_Camera.hpp"        // For the camera
#include "OGL_Time.hpp"          // For time

#include "../ThirdParty/glm/gtc/type_ptr.hpp" // Type shit idk

/* Main render view of the program */
extern OGL_Camera* OGL_RenderView;

/**
 * @brief Bind a camera to the active render view
 * 
 * @param cam Camera to assign
 */
void OGL_BindCameraToRenderView(OGL_Camera* cam);

/**
 * @brief Pre draws to the window, sets OpenGL's state
 * 
 * @param graphicsPipeline Instruct what graphics pipeline to use
 */
void OGL_PreDraw(GLuint graphicsPipeline);

/**
 * @brief Pre draws to the window, sets OpenGL's state for text
 * 
 * @param graphicsPipeline Instruct what graphics pipeline to use
 */
void OGL_PreDrawText(GLuint graphicsPipeline);

/**
 * @brief Draws the pre-drawn assets to the window
 * 
 * @param object Vertex object to draw 
 *  
 * @note VAO Vertex array object to draw
 * @note VBO Vertex buffer object to draw from (not required, since the VAO has all the data we want)
 * @note IBO Index buffer object (rendering order of vertices)
 */
void OGL_Draw(OGL_VertexObject* object);

/**
 * @brief Draws an object
 * 
 * @param object Object to draw
 */
void OGL_DrawObject(OGL_VertexObject* object);

/**
 * @brief Sets the screen's background
 * to a specifed colour, this data is
 * saved in a buffer where other objects
 * live, so it has to be done before
 * rendering OGL_VertexObject's
 * in order not to mess with their buffers
 * 
 * @param r Red value from 0 to 1.0 (0 to 255)
 * @param g Green value from 0 to 1.0 (0 to 255)
 * @param b Blue value from 0 to 1.0 (0 to 255)
 * @param a ALpha value from 0 to 1.0 (0 to 255)
 */
void OGL_SetScreenBackground(float r, float g, float b, float a);

/**
 * @brief Render an object, handle pre-draw/ and draw
 * as well as uniforms
 * 
 * @note Uniforms we can use in shaders:
 *  // Model
 *  # uTrans - Object transformation
 *  # uScale - Object scaling
 *  # uRotate - Object rotation
 * 
 *  // Camera
 *  uView - Render view's (active camera's) view matrix
 *  uProj - Render view's (active camera's) projection matrix
 * 
 *  // Misc
 *  uColor - Object coloring, only if the object as no UV, and the shader uses it
 * 
 * @param object Object to render
 * @param uniformsMissing Boolean if we want to pass more uniforms to an object, BUT we need to call OGL_Draw(obj.mesh) ourselves later!
 */
void OGL_Render(OGL_Object* object, bool uniformsMissing = false);

/**
 * @brief Vist and render all of the given
 * root's children
 *
 * @param root Root to render the children of
 */
void OGL_RenderVisitChildren(OGL_ONode* root);

