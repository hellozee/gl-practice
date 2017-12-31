#include "mesh.h"

Mesh::Mesh(GLfloat *meshData,unsigned int numVerts)
{
    _drawCount = numVerts/8;
    glGenVertexArrays(1,&_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1,&_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    glBufferData(GL_ARRAY_BUFFER,numVerts * sizeof(meshData[0]),meshData,GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(GLvoid*)(3*sizeof(GLfloat)));

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1,&_vbo);
    glDeleteVertexArrays(1,&_vao);
}

void Mesh::Draw(GLuint program)
{
    glBindVertexArray(_vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(glGetUniformLocation(program,"tex"),0);

    glDrawArrays(GL_TRIANGLES,0,_drawCount);

    glBindVertexArray(0);
}

void Mesh::addTexture(const char *path){

    glGenTextures(1,&_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Set the _texture wrapping parametersusing different buffer objects for texture and vertices
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
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(sizeof(GLfloat) * 6));
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