#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display{

public:
    Display(int width, int height, const std::string &title);
    ~Display();

    inline bool isClosed(){return _isClosed;}
    void swapBuffers();
    void clear(float r,float g,float b,float a);

private:
    SDL_Window *_window;
    SDL_GLContext _glContext;

    bool _isClosed = false;

};