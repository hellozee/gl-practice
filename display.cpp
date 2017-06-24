#include "display.h"

Display::Display(int width, int height, const std::string &title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    _window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
    _glContext = SDL_GL_CreateContext(_window);

    GLenum status = glewInit();

    if(status != GLEW_OK){
        std::cerr << "GLEW failed to initialize." << std::endl;
    }
}

Display::~Display()
{
    SDL_GL_DeleteContext(_glContext);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Display::clear(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::swapBuffers()
{
    SDL_GL_SwapWindow(_window);

    SDL_Event event;

    if(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            _isClosed = true;
        }
        if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_ESCAPE:
                    _isClosed = true;
                    break;
                default:
                    break;
            }
        }
    }
}