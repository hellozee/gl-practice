//Includes
#include "display.h" //For drawing the window, uses SDL
#include "mesh.h"    //For generating the meshes
#include "shader.h"  //Compiling Shaders

int main(){

    Display disp(800,600,"Testing"); // SDL Window for drawing things


    GLfloat meshData[] = {
         0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0,
        -0.5,-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.5,-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0
    };

    //Intializing mesh
    Mesh mesh(meshData,sizeof(meshData)/sizeof(meshData[0]));
    mesh.addTexture("res/container.jpg");
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