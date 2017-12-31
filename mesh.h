#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

//Separate vertex class for better readability
class Vertex{

public:
    Vertex(const glm::vec3 &pos);
private:
    glm::vec3 _pos;

};

class TexCord{

public:
    TexCord(const glm::vec2 &pos);
private:
    glm::vec2 _pos;

};

class Mesh{

public:
    Mesh(Vertex *vertices,unsigned int numVerts,GLuint *indices,unsigned int drawCount);
    ~Mesh();

    void Draw(GLuint program);
    void addTexture(const char * path,TexCord *uv);

private:

    GLuint _vbo,_ebo,_vao,_texture;

    unsigned int _drawCount;
};