#include "OGL_Shader.hpp"

std::unordered_map<std::string, OGL_Shader> OGL_ShaderRegistry;

GLuint OGL_CompileShader(GLuint type, const std::string& sourceCode){
    /* Created shader object */
    GLuint shaderObject;
    
    /* Creating the shader */
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }else{
        std::fprintf(stderr, "OGL_ERR: Unlawful shader type provided, while compiling shaders\n");
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

    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if(!success){
        char log[1024];
        glGetShaderInfoLog(shaderObject, 1024, NULL, log);
        std::fprintf(stderr, "OGL_ERR: Shader compile error: %s\n", log);
    }

    return shaderObject;
}

GLuint OGL_CreateShaderProgram(std::string shaderId, const std::string& vertexShader, const std::string& fragmentShader){
    /* We will fill it's parts with the shaders */
    GLuint programObject = glCreateProgram();

    GLuint VerS = OGL_CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint FraS = OGL_CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programObject, VerS); /* Attach the vertex shader to the program object */
    glAttachShader(programObject, FraS); /* Attach the fragment shader to the program object */
    glLinkProgram(programObject);

    /* Validate the program */
    glValidateProgram(programObject);

    OGL_ShaderRegistry.insert({shaderId, programObject});

    return programObject;
}

void OGL_InitShaderRegistry(void){
    OGL_CreateShaderProgram("rootobj", OGLS_ROOT_OBJ_V, OGLS_ROOT_OBJ_F);
    OGL_CreateShaderProgram("color", OGLS_TRS_MVP_ColorV, OGLS_TRS_MVP_ColorF);
    OGL_CreateShaderProgram("bp_attenuated_tex", OGLS_TRS_MVP_Lit_Blinn_Phong_Texture_AttenuatedV, OGLS_TRS_MVP_Lit_Blinn_Phong_Texture_AttenuatedF);
    OGL_CreateShaderProgram("bp_tex", OGLS_TRS_MVP_Lit_Blinn_Phong_TextureV, OGLS_TRS_MVP_Lit_Blinn_Phong_TextureF);
    OGL_CreateShaderProgram("tex", OGLS_TRS_MVP_TextureV, OGLS_TRS_MVP_TextureF);
    OGL_CreateShaderProgram("glyph", OGLS_GlyphV, OGLS_GlyphF);
}

OGL_Shader OGL_GetShader(std::string id){
    return OGL_ShaderRegistry.find(id)->second;
}