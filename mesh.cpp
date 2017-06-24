#include "mesh.h"

Mesh::Mesh(Vertex *vertices,unsigned int numVerts)
{
    _drawCount = numVerts;

    glGenVertexArrays(1,&_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS,_buffers);
    glBindBuffer(GL_ARRAY_BUFFER,_buffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,_drawCount * sizeof(vertices[0]),vertices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{   
    glDeleteVertexArrays(1,&_VAO);
}

void Mesh::Draw()
{
    glBindVertexArray(_VAO);

    glDrawArrays(GL_QUADS,0,_drawCount);

    glBindVertexArray(0);
}

Vertex::Vertex(const glm::vec3 &pos) :
_pos(pos)
{
}