# SDL2 Window main

CXXC = g++

SRCP = src/

SRC = $(SRCP)main.cpp\
$(SRCP)SDL2_Event.cpp\
$(SRCP)SDL2_InitWin.cpp\
$(SRCP)OGL_InitContext.cpp\
$(SRCP)OGL_Render.cpp\
$(SRCP)OGL_Triangle.cpp\
$(SRCP)OGL_Quad.cpp\
$(SRCP)OGL_Shader.cpp\
$(SRCP)OGL_Object.cpp\
$(SRCP)OGL_TextureQuad.cpp

# Third Party
INCL = -IThirdParty/SDL2/include/

# For SDL2
SDL2L = -LThirdParty/SDL2/lib
SDL2F = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# For OpenGL
GLADSRC = ThirdParty/GLAD/src/glad.c

SDL2WIN:
	$(CXXC) $(SRC) $(GLADSRC) $(INCL) $(SDL2L) $(SDL2F) -o bin/win
