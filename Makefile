all:
	g++ -o GLWindow main.cpp texture.cpp display.cpp mesh.cpp shader.cpp -lSDL2 -lGLEW -lGL -lSOIL
