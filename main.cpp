//Includes
#include "display.h" //For drawing the window, uses SDL
#include "mesh.h"    //For generating the meshes
#include "shader.h"  //Compiling Shaders

int main(){

    Display disp(800,600,"Testing"); // SDL Window for drawing things

    //Vertex of the mesh which is to be drawn
    Vertex vertices[] = { Vertex(glm::vec3( 0.5, 0.5,0)),
                          Vertex(glm::vec3( 0.5,-0.5,0)),
                          Vertex(glm::vec3(-0.5,-0.5,0)),
                          Vertex(glm::vec3(-0.5, 0.5,0))};
                          
    GLuint indices[] = {0,1,3,1,2,3};

    //Texture Coordinates
    TexCord uvs[] = {TexCord(glm::vec2( 1.0, 1.0)),
                     TexCord(glm::vec2( 1.0, 0.0)),
                     TexCord(glm::vec2( 0.0, 0.0)),
                     TexCord(glm::vec2( 0.0, 1.0))};

    //Intializing mesh
    Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]),indices,sizeof(indices)/sizeof(indices[0]));
    mesh.addTexture("res/brick.jpg",uvs);
    //Fetching Shaders
    Shader shader("res/shader");

    while(!disp.isClosed()){
        //Clearing the screen to draw
        disp.clear(0.8f,0.8f,0.8f,1.0f);
        //Attaching the shader to the program
        shader.Bind();
        //Drawing the mesh
        mesh.Draw(shader.program);
        //Now Displying what is drawn
        disp.swapBuffers();
    }

    return 0;
}