#pragma once

#include <string>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <assert.h>
#include <glm/glm.hpp>
#include "shader.h"

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