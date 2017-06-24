#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

int main(){

    Display disp(800,600,"Testing");

    Vertex vertices[] = { Vertex(glm::vec3(-0.5, 0.5,0)),
                          Vertex(glm::vec3( 0.5, 0.5,0)),
                          Vertex(glm::vec3( 0.5,-0.5,0)),
                          Vertex(glm::vec3(-0.5,-0.5,0))};
    
    TexCord uvs[] = {TexCord(glm::vec2(-1.0, 1.0)),
                     TexCord(glm::vec2( 1.0, 1.0)),
                     TexCord(glm::vec2( 1.0, -1.0)),
                     TexCord(glm::vec2(-1.0, -1.0))};

    Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]));
    Shader shader("res/shader");
    Texture tex("res/brick.jpg",uvs);

    while(!disp.isClosed()){
        disp.clear(1.0f,1.0f,1.0f,1.0f);
        shader.Bind();
        tex.Bind();
        mesh.Draw();
        disp.swapBuffers();
    }

    return 0;
}