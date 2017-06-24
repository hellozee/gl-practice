#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{

public:
    Vertex(const glm::vec3 &pos);
private:
    glm::vec3 _pos;

};

class Mesh{

public:
    Mesh(Vertex *vertices,unsigned int numVerts);
    ~Mesh();

    void Draw();

private:

    enum{
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint _VAO;
    GLuint _buffers[NUM_BUFFERS];

    unsigned int _drawCount;
};