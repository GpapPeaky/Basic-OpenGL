#include "OGL_Material.hpp"

OGL_Material OGL_CreateMaterial(float ambient[3], float diffuse[3], float specular[3], float shininess, float  emit[3], float emissiveness){
    OGL_Material mat;

    mat.ambient[0] = ambient[0];
    mat.ambient[1] = ambient[1];
    mat.ambient[2] = ambient[2];

    mat.diffuse[0] = diffuse[0];
    mat.diffuse[1] = diffuse[1];
    mat.diffuse[2] = diffuse[2];

    mat.specular[0] = specular[0];
    mat.specular[1] = specular[1];
    mat.specular[2] = specular[2];

    mat.shininess = shininess;
    
    mat.emit[0] = emit[0];
    mat.emit[1] = emit[1];
    mat.emit[2] = emit[2];
    
    mat.emissiveness = emissiveness;

    return mat;
}
