all:
	g++ -o GLWindow -Wall -Wextra -std=c++11 main.cpp ui/display.cpp draw/mesh.cpp draw/shader.cpp ui/camera.cpp -lSDL2 -lGLEW -lGL -lSDL2_image
