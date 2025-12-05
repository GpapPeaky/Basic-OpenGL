#include "OGL_Object.hpp"

OGL_Object* OGL_CreateObject(GLuint s){
    OGL_Object* newObj = new OGL_Object;
    newObj->mesh = new OGL_VertexObject; /* Or render mesh */
    newObj->shader = s;

    /* The mesh will be populated elsewhere */

    return newObj;
}

void OGL_AssignColorToObject(OGL_Object* obj, float r, float g, float b, float a){
    if(!obj){
        std::fprintf(stderr, "OGL_ERR: Null object to assign colour\n");

        return;
    }

    obj->color[0] = r;
    obj->color[1] = g;
    obj->color[2] = b;
    obj->color[3] = a;

    return;
}

void OGL_AssignMaterialToObject(OGL_Object* obj, OGL_Material mat){
    if(!obj){
        std::fprintf(stderr, "OGL_ERR: Null object to assign material\n");

        return;
    }

    obj->mat = mat;
    
    return;
}
