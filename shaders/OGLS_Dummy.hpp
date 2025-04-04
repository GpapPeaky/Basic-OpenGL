#include <string>

/**
 * @brief Rainbow vertex shader string
 */
const std::string OGLS_RainbowV =
    "#version 410 core\n"
    "layout(location=0) in vec3 pos; // Layout of the vertex in the VAO\n"
    "layout(location=1) in vec3 rgb;\n"
    "out vec3 v_vRGB; // will give it to the fragment shader\n"
    "void main()\n"
    "{\n"
    "   v_vRGB = rgb; // we pass the values of the RGBVBO\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f); // We use the pos vertices for the position\n"
    "}\n";

/**
 * @brief Rainbow fragment shader string
 */
const std::string OGLS_RainbowF = 
    "#version 410 core\n"
    "in vec3 v_vRGB; // Takes it from the vertex shader\n"
    "out vec4 fragColour;\n"
    "void main()\n"
    "{\n"
    "   fragColour = vec4(v_vRGB, 1.0f);\n"
    "}\n";
