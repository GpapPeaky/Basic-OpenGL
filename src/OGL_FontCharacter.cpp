#include "OGL_FontCharacter.hpp"

std::map<char, OGL_Character> OGL_LoadCharacters(FT_Face face){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    std::map<char, OGL_Character> characters;

    for(unsigned char c = 0 ; c < 128 ; c++){
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // now store character for later use
        OGL_Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        
        characters.insert(std::pair<char, OGL_Character>(c, character));
    }

    FT_Done_Face(face);
    // FT_Done_FreeType(ft);

    return characters;
}

void OGL_RenderText(OGL_Object& obj, std::string text, float x, float y, float scale, glm::vec3 color, std::map<char, OGL_Character>& characters){
    OGL_PreDrawText(obj.mat.shader);

    glUniform1i(
        glGetUniformLocation(obj.mat.shader, "text"),
        0
    );

    glm::mat4 projection = glm::ortho(
        0.0f,
        (float)SDL2_WinWidth,
        (float)SDL2_WinHeight,
        0.0f
    );

    glUniformMatrix4fv(
        glGetUniformLocation(obj.mat.shader, "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );

    // activate corresponding render state	
    glUniform3f(glGetUniformLocation(obj.mat.shader, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(obj.mesh->VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin() ; c != text.end() ; c++) {
        OGL_Character ch = characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - ch.bearing.y * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos,       0.0f, 0.0f },
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },

            { xpos,     ypos,       0.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.tid);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}