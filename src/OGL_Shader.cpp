#include "OGL_Shader.hpp"

GLuint OGL_CompileShader(GLuint type, const std::string& sourceCode){
    /* Created shader object */
    GLuint shaderObject;
    
    /* Creating the shader */
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }else{
        std::fprintf(stderr, "Unlawful shader type provided, while compiling shaders\n");
        return 0;
    }

    /* Set up the shader source code */
    const char* src = sourceCode.c_str(); /* We can only pass char* due to CLang */
    glShaderSource(shaderObject, // What shader object to compile into
                1, // Amount of shader to compile
                &src, // Shader source code
                NULL);
    /* Compile the shader */
    glCompileShader(shaderObject);

    return shaderObject;
}

GLuint OGL_CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader){
    /* We will fill it's parts with the shaders */
    GLuint programObject = glCreateProgram();

    GLuint VerS = OGL_CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint FraS = OGL_CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programObject, VerS); /* Attach the vertex shader to the program object */
    glAttachShader(programObject, FraS); /* Attach the fragment shader to the program object */
    glLinkProgram(programObject);

    /* Validate the program */
    glValidateProgram(programObject);

    return programObject;
}
