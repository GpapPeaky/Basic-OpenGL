#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "OGL_Object.hpp"
#include "OGL_Controller.hpp"

/**
 * @brief Handles main loop events
 * 
 * @param quit Checks if we have quit the main loop
 * @param ctrl Controller to handle.
 */
void SDL2_HandleEvents(bool& quit, OGL_Controller* ctrl);
