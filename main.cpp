//Includes
#include "display.h" //For drawing the window, uses SDL
#include "mesh.h"    //For generating the meshes
#include "shader.h"  //Compiling Shaders
#include "texture.h" //Displaying textures, this one still has problems when applying textures

int main(){

    Display disp(800,600,"Testing"); // SDL Window for drawing things

    //Vertex of the mesh which is to be drawn
    Vertex vertices[] = { Vertex(glm::vec3(-0.5, 0.5,0)),
                          Vertex(glm::vec3( 0.5, 0.5,0)),
                          Vertex(glm::vec3( 0.5,-0.5,0)),
                          Vertex(glm::vec3(-0.5,-0.5,0))};
    
    //Texture Coordinates
    TexCord uvs[] = {TexCord(glm::vec2(-1.0, 1.0)),
                     TexCord(glm::vec2( 1.0, 1.0)),
                     TexCord(glm::vec2( 1.0, -1.0)),
                     TexCord(glm::vec2(-1.0, -1.0))};

    //Intializing mesh
    Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]));
    //Fetching Shaders
    Shader shader("res/shader");
    //Loading the texture
    Texture tex("res/brick.jpg",uvs);

    while(!disp.isClosed()){
        //Clearing the screen to draw
        disp.clear(1.0f,1.0f,1.0f,1.0f);
        //Attaching the shader to the program
        shader.Bind();
        //Applying textures !!
        tex.Bind();
        //Drawing the mesh
        mesh.Draw();
        //Now Displying what is drawn
        disp.swapBuffers();
    }

    return 0;
}