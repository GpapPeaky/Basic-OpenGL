#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"    /* SDL2 */
#include "../ThirdParty/GLAD/include/glad/glad.h"   /* GLAD */

#include <array>

/* An object's material data */
typedef struct OGL_Material{
    std::array<float, 3> ambient    = {0.0f, 0.0f, 0.0f};        /* Object's color under ambient light */ 
    std::array<float, 3> diffuse    = {0.0f, 0.0f, 0.0f};        /* Object's color under diffuse light */
    std::array<float, 3> specular   = {0.0f, 0.0f, 0.0f};        /* Object's color under specular light */
    float shininess                 = 0.0f;                      /* How shiny the object is, intensity of the specular light */
    std::array<float, 3> emit       = {0.0f, 0.0f, 0.0f};        /* Object's emission colour */
    float emissiveness              = 0.0f;                      /* Emit light intensity */

    GLuint shader = 0;
    GLuint texture = 0;
}OGL_Material;

/**
 * @brief Create a custom object material
 * 
 * @param ambient Colour under ambient light
 * @param diffuse Colour under diffuse light
 * @param specular Colour uder specular light
 * @param shininess Specular intensity
 * @param emit Colour emitting
 * @param emissiveness Emit intensity
 * 
 * @returns The newly created material
 */
OGL_Material OGL_CreateMaterial(std::array<float, 3> ambient, std::array<float, 3> diffuse, std::array<float, 3> specular, float shininess, std::array<float, 3> emit, float emissiveness);
