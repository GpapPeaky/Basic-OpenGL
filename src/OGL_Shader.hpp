#pragma once

#include "../ThirdParty/GLAD/include/glad/glad.h"
#include "../shaders/OGLS.hpp"

#include <string>
#include <unordered_map>

extern std::unordered_map<std::string, OGL_Shader> OGL_ShaderRegistry; /* All available shaders are here */

/**
 * @brief Compiles the given shader source
 * 
 * @param type Type of shader (Vertex/Fragment)
 * @param sourceCode Shader source code
 * 
 * @returns The created shader
 */
GLuint OGL_CompileShader(GLuint type, const std::string& sourceCode);

/**
 * @brief Creates a shader program, that will store the shaders onto an object
 * 
 * @param shaderId String for a shader id inside the registry
 * @param vertexShader String containing the source of the vertex shader
 * @param fragmentShader String containing the source of the fragment shader
 * 
 * @returns A handle to the shader program object
 */ 
GLuint OGL_CreateShaderProgram(std::string shaderId, const std::string& vertexShader, const std::string& fragmentShader);

/**
 * @brief Initializes the shader registry so we don't need to make any of the shaders ourselves
 */
void OGL_InitShaderRegistry(void);

/**
 * @brief Get a shader from the shader registry
 * 
 * @param id Shader id
 * 
 * @returns The created shader program
 */
OGL_Shader OGL_GetShader(std::string id);
