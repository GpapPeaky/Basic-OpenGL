#pragma once

#include "OGL_Object.hpp"

namespace TRS{
    /**
     * @brief Translates the object to the new array
     * 
     * @param obj Object to transalate
     * @param translation Translation array
     */
    void T(OGL_Object& obj, std::array<float, 3> translation);

    /**
     * @brief Rotates an object based on a rotation array
     * 
     * @param obj Object to rotate
     * @param rotation Rotation array
     */
    void R(OGL_Object& obj, std::array<float, 3> rotation);

    /**
     * @brief Scales an object based on a scaling array
     * 
     * @param obj Object to scale
     * @param scaling Scaling array
     */
    void S(OGL_Object& obj, std::array<float, 3> scaling);
} /* TRS functions for objects */