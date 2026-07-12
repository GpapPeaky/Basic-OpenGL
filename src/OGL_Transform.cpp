#include "OGL_Transform.hpp"

void TRS::T(OGL_Object& obj, std::array<float, 3> translation){
    obj.position = translation;
}

void TRS::R(OGL_Object& obj, std::array<float, 3> rotation){
    obj.rotation = rotation;
}

void TRS::S(OGL_Object& obj, std::array<float, 3> scaling){
    obj.scale = scaling;
}
