#pragma once

#include <string>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <assert.h>
#include <glm/glm.hpp>
#include "shader.h"

//Totaly mixed up my texture class, thanks to opengl for providing a 100 different ways
//of doing the same thing


//Is this needed? A class for keeping track of the UVs
class TexCord{

public:
    TexCord(const glm::vec2 &pos);
private:
    glm::vec2 _pos;

};

class Texture{

public:
    Texture(const std::string &path,TexCord *uv);
    ~Texture();

    void Bind();

private:
    GLuint _texture;
};