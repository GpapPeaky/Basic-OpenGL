#include <string>

/**
 * @brief Rainbow vertex shader string
 */
const std::string OGLS_DummyV =
    "#version 410 core\n"
    "layout(location=0) in vec3 pos; // Layout of the vertex in the VAO\n"
    "layout(location=1) in vec3 rgb;\n"
    "out vec3 colour; // will give it to the fragment shader\n"
    "uniform float u_time; // time \n"
    "void main()\n"
    "{\n"
    "   colour = rgb;\n"
    "   float explode = abs(sin(u_time * 0.5)) * 1.5; // grows and shrinks\n"
    "   float wave = sin(pos.x * 4.0 + u_time * 2.0) * 0.2;\n"
    "   // Move vertex outward based on its original direction \n"
    "   vec3 displacedPos = pos + normalize(pos) * explode + vec3(0.0, wave, 0.0); \n" 
    "   gl_Position = vec4(displacedPos, 1.0f); // We use the pos vertices for the position\n"
    "}\n";

/**
 * @brief Rainbow fragment shader string
 */
const std::string OGLS_DummyF = 
    "#version 410 core\n"
    "in vec3 colour; // Takes it from the vertex shader\n"
    "out vec4 fragColour;\n"
    "void main()\n"
    "{\n"
    "   fragColour = vec4(colour, 1.0f);\n"
    "}\n";
