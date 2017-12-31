#include "mesh.h"

Mesh::Mesh(Vertex *vertices,unsigned int numVerts,GLuint *indices,unsigned int drawCount):
_drawCount(drawCount)
{

    glGenVertexArrays(1,&_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1,&_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    glBufferData(GL_ARRAY_BUFFER,numVerts * sizeof(vertices[0]),vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_drawCount*sizeof(indices[0]),indices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
    glDeleteVertexArrays(1,&_vao);
}

void Mesh::Draw(GLuint program)
{
    glBindVertexArray(_vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(glGetUniformLocation(program,"tex1"),0);

    glDrawElements(GL_TRIANGLES,_drawCount,GL_UNSIGNED_INT,0);

    glBindVertexArray(0);
}

void Mesh::addTexture(const char *path,TexCord *uv){
    
    glGenTextures(1,&_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Set the _texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set _texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set _texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create _texture and generate mipmaps
    int width,height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D,0);

    glBindVertexArray(_vao);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2 * sizeof(GLfloat),(GLvoid*)(0));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

Vertex::Vertex(const glm::vec3 &pos) :
_pos(pos)
{
}

TexCord::TexCord(const glm::vec2 &pos):
_pos(pos)
{

}