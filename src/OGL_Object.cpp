#include "OGL_Object.hpp"

OGL_Object* OGL_CreateObject(GLuint s){
    OGL_Object* newObj = new OGL_Object;
    newObj->mesh = new OGL_VertexObject{}; /* Or render mesh */
    newObj->position = {0.0f, 0.0f, 0.0f};
    newObj->rotation = {0.0f, 0.0f, 0.0f};
    newObj->scale    = {1.0f, 1.0f, 1.0f};
    
    newObj->mesh = new OGL_VertexObject{};
    newObj->mat.shader = s;
    
    /* The mesh will be populated elsewhere */
    
    return newObj;
}

void OGL_AssignColorToObject(OGL_Object* obj, float r, float g, float b, float a){
    if(!obj){
        std::fprintf(stderr, "OGL_ERR: Null object to assign colour\n");

        return;
    }

    obj->mat.diffuse[0] = r;
    obj->mat.diffuse[1] = g;
    obj->mat.diffuse[2] = b;

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

glm::mat4 OGL_GetModel(const OGL_Object& obj){
    glm::mat4 model(1.0f);

    // Translation
    model = glm::translate(
        model,
        glm::vec3(
            obj.position[0],
            obj.position[1],
            obj.position[2]
        )
    );

    // Rotation (degrees)
    model = glm::rotate(
        model,
        glm::radians(obj.rotation[0]),
        glm::vec3(1, 0, 0)
    );

    model = glm::rotate(
        model,
        glm::radians(obj.rotation[1]),
        glm::vec3(0, 1, 0)
    );

    model = glm::rotate(
        model,
        glm::radians(obj.rotation[2]),
        glm::vec3(0, 0, 1)
    );

    // Scale
    model = glm::scale(
        model,
        glm::vec3(
            obj.scale[0],
            obj.scale[1],
            obj.scale[2]
        )
    );

    return model;
}
