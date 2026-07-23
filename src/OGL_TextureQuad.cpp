#include "OGL_TextureQuad.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb_image/stb_image.h"  /* Image loading */

void OGL_CreateTextureQuad(OGL_VertexObject& object){
    object.verticesCount = 6; /* 6 vertices for 2 triangles */

    // In OpenGL, the origin is at the center and the y-axis is flipped, negatives at the top.
    // in bitmaps the origin is at the top left!

    // Vertex data: position (x, y, z), color (r, g, b), texture coords (s, t)
    const std::vector<GLfloat> vertices = {
        // Positions                   // Colors          // TexCoords
        -1.0f, -1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // Bottom Left
         1.0f, -1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Bottom Right
         1.0f,  1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Top Right
        -1.0f,  1.0f, 0.0f,            0.0f, 0.0f, 0.0f,  1.0f, 0.0f   // Top Left
    };

    /* Index buffer (EBO/IBO) */
    /* This can sometimes break things */
    const std::vector<GLuint> indices {
        0, 1, 2,
        0, 2, 3 };

    /* Generate and bind VAO */
    glGenVertexArrays(1, &object.VAO);
    glBindVertexArray(object.VAO);

    /* Generate and bind VBO */
    glGenBuffers(1, &object.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    /* Generate and bind IBO */
    glGenBuffers(1, &object.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    /* Define vertex attributes */
    
    // Position Attribute (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);

    // Color Attribute (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));

    // Texture Coordinate Attribute (location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));

    /* Unbind VAO (good practice) */
    glBindVertexArray(0);

    /* Disable attributes */
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    return;
}

void OGL_CreateTextQuad(OGL_VertexObject& object){
    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);

    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 6 * 4,
        nullptr,
        GL_DYNAMIC_DRAW
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 4,
        nullptr
    );

    glBindVertexArray(0);
}

void OGL_LoadBitmapToObject(OGL_Object& object, const char* bitmap){
    glGenTextures(1, &object.mat.texture.texture);
    glBindTexture(GL_TEXTURE_2D, object.mat.texture.texture); /* Bind the texture, and it's type */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Anti-aliasing, kind of bad
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Crisp pixel perfect
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int w, h, channels;
    unsigned char* data = stbi_load(bitmap, &w, &h, &channels, 0);

    if(data){
        if(w > 0 && h > 0){
            GLenum format = (channels == 3) ? GL_RGB : GL_RGBA; /* See what colour format we can use based on the bitmap provided */

            /* Upload texture to OpenGL */
            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D); /* Texture scaling mipmaps */

            /* Save bitmap data for later use */
            object.mat.texture.cpuPixels = new unsigned char[w * h * channels];

            std::memcpy( /* Copy memory */
                object.mat.texture.cpuPixels,
                data,
                w * h * channels
            );

            object.mat.texture.width = w;
            object.mat.texture.height = h;
            object.mat.texture.channels = channels;
        }
    }else{
        std::fprintf(stderr, "OGL_ERR: Failed to load bitmap %s (%s)\n", bitmap, stbi_failure_reason());
    }

    /* Free the data here */
    stbi_image_free(data);

    return;
}

std::array<unsigned char, 3> OGL_GetHoveredColourFromTexture(const OGL_Texture& texture, const glm::mat4& model, OGL_Camera* cam){
    if(!texture.cpuPixels){
        std::fprintf(stderr, "OGL_ERR: Texture has no CPU pixel data\n");
        return {0, 0, 0};
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int windowWidth, windowHeight;
    SDL_GetWindowSize(SDL2_Win, &windowWidth, &windowHeight);

    // Mouse -> Normalized Device Coordinates
    float ndcX = (2.0f * mouseX) / windowWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / windowHeight;

    glm::vec4 rayClip(ndcX, ndcY, -1.0f, 1.0f);

    glm::mat4 projection = OGL_GetProjMatrix(cam);
    glm::mat4 view = OGL_GetViewMatrix(cam);

    // Clip -> Eye
    glm::vec4 rayEye = glm::inverse(projection) * rayClip;
    rayEye.z = -1.0f;
    rayEye.w = 0.0f;

    // Eye -> World
    glm::vec3 rayDir = glm::normalize(
        glm::vec3(glm::inverse(view) * rayEye));

    glm::vec3 rayOrigin = cam->pos;

    // World -> Local
    glm::mat4 invModel = glm::inverse(model);

    glm::vec3 localOrigin =
        glm::vec3(invModel * glm::vec4(rayOrigin, 1.0f));

    glm::vec3 localDir =
        glm::normalize(glm::vec3(invModel * glm::vec4(rayDir, 0.0f)));

    // Intersect with local Z = 0 plane
    if (fabs(localDir.z) < 1e-6f)
        return {0, 0, 0};

    float t = -localOrigin.z / localDir.z;

    if (t < 0.0f)
        return {0, 0, 0};

    glm::vec3 hit = localOrigin + t * localDir;

    // Outside quad?
    if (hit.x < -1.0f || hit.x > 1.0f ||
        hit.y < -1.0f || hit.y > 1.0f)
        return {0, 0, 0};

    // Local -> UV
    float u = (hit.x + 1.0f) * 0.5f;          // reverted — no flip
    float v = (hit.y + 1.0f) * 0.5f;   // flipped from before

    int px = glm::clamp(
        int(u * texture.width),
        0,
        texture.width - 1);
        
    int py = glm::clamp(
        int(v * texture.height),
        0,
        texture.height - 1);
            
    // Need to alloc memory fro cpuPixels?
    const unsigned char* p =
        texture.cpuPixels +
        (py * texture.width + px) * texture.channels;

    return { p[0], p[1], p[2] };
}
