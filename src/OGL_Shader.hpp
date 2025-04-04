#pragma once

#include "../ThirdParty/GLAD/include/glad/glad.h"

#include <string>

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
 * @param vertexShader String containing the source of the vertex shader
 * @param fragmentShader String containing the source of the fragment shader
 * 
 * @returns A handle to the shader program object
 */ 
GLuint OGL_CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
