# Compiler
CXX = g++
CC = gcc

OBJDIR = obj
BINDIR = bin

INCL = -IThirdParty/SDL2/include/
SDL2L = -LThirdParty/SDL2/lib
SDL2F = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# GLAD
#
# For the glad.o object file
# gcc -c ThirdParty/GLAD/src/glad.c -o obj/glad.o -IThirdParty/GLAD/include
#  
#
GLADSRC = ThirdParty/GLAD/src/glad.c
GLADOBJ = $(OBJDIR)/glad.o

# Object files
OBJS = \
    $(OBJDIR)/main.o \
    $(OBJDIR)/SDL2_Event.o \
    $(OBJDIR)/SDL2_InitWin.o \
    $(OBJDIR)/OGL_InitContext.o \
    $(OBJDIR)/OGL_Render.o \
    $(OBJDIR)/OGL_Triangle.o \
    $(OBJDIR)/OGL_Quad.o \
    $(OBJDIR)/OGL_Shader.o \
    $(OBJDIR)/OGL_Object.o \
    $(OBJDIR)/OGL_TextureQuad.o \
    $(OBJDIR)/OGL_Cube.o \
    $(OBJDIR)/OGL_Camera.o \
    $(OBJDIR)/OGL_Controller.o \
	$(OBJDIR)/OGLS.o

all: $(BINDIR)/win

# Link -------------------------------------------------------------------

$(BINDIR)/win: $(OBJS) $(GLADOBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJS) $(GLADOBJ) $(SDL2L) $(SDL2F) -o $@

# GLAD -------------------------------------------------------------------

$(OBJDIR)/glad.o: $(GLADSRC)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(INCL)

# Rules for every .cpp ---------------------------------------------------

$(OBJDIR)/main.o: src/main.cpp $(AUXF) $(SHADERS)
	@mkdir -p $(OBJDIR)
	$(CXX) -c src/main.cpp -o $(OBJDIR)/main.o $(INCL)

$(OBJDIR)/OGLS.o: shaders/OGLS.cpp shaders/OGLS.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c shaders/OGLS.cpp -o $(OBJDIR)/OGLS.o $(INCL)

$(OBJDIR)/SDL2_Event.o: src/SDL2_Event.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/SDL2_InitWin.o: src/SDL2_InitWin.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_InitContext.o: src/OGL_InitContext.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Render.o: src/OGL_Render.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Triangle.o: src/OGL_Triangle.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Quad.o: src/OGL_Quad.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Shader.o: src/OGL_Shader.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Object.o: src/OGL_Object.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_TextureQuad.o: src/OGL_TextureQuad.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Cube.o: src/OGL_Cube.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Camera.o: src/OGL_Camera.cpp
	$(CXX) -c $< -o $@ $(INCL)

$(OBJDIR)/OGL_Controller.o: src/OGL_Controller.cpp
	$(CXX) -c $< -o $@ $(INCL)

# Clean ------------------------------------------------------------------

clean:
	rm -rf $(OBJDIR) $(BINDIR)/win
