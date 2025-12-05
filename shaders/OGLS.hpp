#pragma once

#include <string>

#include "../ThirdParty/GLAD/include/glad/glad.h"

typedef unsigned int OGL_Shader; /* More descriptive */

extern std::string OGLS_TRS_MVP_ColorV;
extern std::string OGLS_TRS_MVP_ColorF;

extern std::string OGLS_TRS_MVP_TextureV;
extern std::string OGLS_TRS_MVP_TextureF;

extern std::string OGLS_ROOT_OBJ_V;
extern std::string OGLS_ROOT_OBJ_F;

extern std::string OGLS_TRS_MVP_Lit_Blinn_Phong_TextureV;
extern std::string OGLS_TRS_MVP_Lit_Blinn_Phong_TextureF;

extern std::string OGLS_TRS_MVP_Lit_Blinn_Phong_Texture_AttenuatedV;
extern std::string OGLS_TRS_MVP_Lit_Blinn_Phong_Texture_AttenuatedF;
