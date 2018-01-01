//Includes
#include "ui/display.h" //For drawing the window, uses SDL
#include "draw/mesh.h"    //For generating the meshes
#include "draw/shader.h"  //Compiling Shaders
#include "ui/camera.h"  //Camera Controls

int main(){

    const int WIDTH = 800, HEIGHT = 600;

    GLfloat ratio = (GLfloat) WIDTH/ (GLfloat) HEIGHT;

    Display disp(WIDTH,HEIGHT,"Testing"); // SDL Window for drawing things

    //Mesh Data structured as {x, y, z, r, g, b, u, v}

    std::vector<GLfloat> meshData = {
         0.0, 0.5,0,0.0,0.0,0.0,0.5,1.0,
        -0.5,-0.5,0,0.0,0.0,0.0,0.0,0.0,
         0.5,-0.5,0,0.0,0.0,0.0,1.0,0.0
    };

    //Intializing mesh
    Mesh mesh(meshData);
    mesh.addTexture("textures/container.jpg");

    //Fetching Shaders
    Shader shader("shaders/shader.vs","shaders/shader.fs");

    //Creating the camera
    Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, ratio, 0.1f, 100.0f);

    while(!disp.isClosed()){
        //Clearing the screen to draw
        disp.clear(0.8f,0.8f,0.8f,1.0f);

        SDL_Event event;

        if(SDL_PollEvent(&event)){
            disp.manageEvents(event);
            cam.manageEvents(event);
        }

        //Attaching the shader to the program
        shader.Bind();

        cam.Use(shader.program);
        cam.doMovement(SDL_GetTicks());

        //Drawing the mesh
        mesh.Draw(shader.program);

        //Now Displying what is drawn
        disp.swapBuffers();
    }

    return 0;
}