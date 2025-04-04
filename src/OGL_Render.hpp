#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../ThirdParty/GLAD/include/glad/glad.h"

#include "SDL2_InitWin.hpp" // For creating the shader object to be used in the graphics pipeline

#include "OGL_Shader.hpp" // For creating the shader object to be used in the graphics pipeline
#include "OGL_Object.hpp" // For the vertex object abstraction

/**
 * @brief Creates the graphics pipeline, with the vertex and
 * fragment shader
 * 
 * @param vs Vertex shader to attach to the object
 * @param fs Fragment shader to attach to the object
 * 
 * @returns Object to store the shaders
 */
GLuint OGL_CreateGraphicsPipeline(const std::string& vs, const std::string& fs);
 
/**
 * @brief Pre draws to the window, sets OpenGL's state
 * 
 * @param graphicsPipeline Instruct what graphics pipeline to use
 */
void OGL_PreDraw(GLuint graphicsPipeline);

/**
 * @brief Draws the pre-drawn assets to the window
 * 
 * @param object Vertex object to draw 
 *  
 * @note VAO Vertex array object to draw
 * @note VBO Vertex buffer object to draw from (not required, since the VAO has all the data we want)
 * @note IBO Index buffer object (rendering order of vertices)
 */
void OGL_Draw(OGL_VertexObject& object);

/**
 * @brief Draws an object
 * 
 * @param object Object to draw
 */
void OGL_DrawObject(OGL_VertexObject& object);

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
