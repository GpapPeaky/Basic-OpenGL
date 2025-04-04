#include <string>

/**
 * @brief Texture vertex shader string
 */
const std::string OGLS_TextureV =
    "#version 410 core\n"
    "layout (location = 0) in vec3 aPos; // Position\n"
    "layout (location = 1) in vec3 aColor; // Color\n"
    "layout (location = 2) in vec2 aTexCoord; // Texture Coordinates\n"
    "out vec2 TexCoord; // Pass the texture coordinates to the fragment shader\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0f); // Set the position of the vertex\n"
    "    TexCoord = aTexCoord; // Pass the texture coordinates to the fragment shader\n"
    "}\n";

/**
 * @brief Texture fragment shader string
 */
const std::string OGLS_TextureF = 
    "#version 410 core\n"
    "in vec2 TexCoord; // Texture coordinates passed from the vertex shader\n"
    "out vec4 FragColor; // Final color output\n"
    "uniform sampler2D ourTexture; // The texture sampler\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(ourTexture, TexCoord); // Sample the texture at the given coordinates\n"
    "}\n";
