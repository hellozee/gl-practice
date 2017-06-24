#include "texture.h"

Texture::Texture(const std::string &path, TexCord *uv)
{   
    int height, width;
    unsigned char *data = SOIL_load_image(path.c_str(),&height,&width,0,SOIL_LOAD_RGB);

    if(!data){
        std::cerr << "Failed to load texture." << path <<  std::endl;
    }

    glGenTextures(1,&_texture);
    glBindTexture(GL_TEXTURE_2D,_texture);

    glTextureParameteri(_texture,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTextureParameteri(_texture,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTextureParameterf(_texture,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTextureParameterf(_texture,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(data);
    glBindTexture(GL_TEXTURE_2D,0);

    //Got upto this
    //Rest is just rubbish, need help
    
    GLuint textureBuffer;
    glGenBuffers(1,&textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,textureBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(uv),uv,GL_STATIC_DRAW);

    GLint texAttrib = glGetAttribLocation(Shader::_program, "coords");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib,2,GL_FLOAT,GL_FALSE,0,(void*)0);

    glBindVertexArray(0);
}

Texture::~Texture()
{
    glDeleteTextures(1,&_texture);
}

void Texture::Bind()
{   
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(Shader::_program, "texture"), 0);
    glBindTexture(GL_TEXTURE_2D,_texture);
}

TexCord::TexCord(const glm::vec2 &pos):
_pos(pos)
{

}