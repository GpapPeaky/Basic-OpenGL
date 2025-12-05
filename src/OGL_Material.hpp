#pragma once

/* An object's material data */
typedef struct OGL_Material{
    float ambient[3];           /* Object's color under ambient light */ 
    float diffuse[3];           /* Object's color under diffuse light */
    float specular[3];          /* Object's color under specular light */
    float shininess;            /* How shiny the object is, intensity of the specular light */
    float emit[3];              /* Object's emission colour */
    float emissiveness;         /* Emit light intensity */
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
OGL_Material OGL_CreateMaterial(float ambient[3], float diffuse[3], float specular[3], float shininess, float  emit[3], float emissiveness);
