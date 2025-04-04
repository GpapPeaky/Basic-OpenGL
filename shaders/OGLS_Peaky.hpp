#include <string>

/**
 * @brief Peaky vertex shader string
 */
const std::string OGLS_PeakyV =
    "#version 410 core\n"
    "in vec4 pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);\n"
    "}\n";

/**
 * @brief Peaky fragment shader string
 */
const std::string OGLS_PeakyF = 
    "#version 410 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";
