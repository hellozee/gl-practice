#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <iostream>


class Camera{

public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, GLfloat fov, GLfloat ratio, GLfloat nearPlane, GLfloat farPlane);
	~Camera();

	void Use(GLuint program);
	void manageEvents(SDL_Event event);
	void doMovement(unsigned int currentFrame);

private:
	glm::mat4 _projection, _view;
	glm::vec3 _cameraPos, _cameraFront, _cameraUp;

	unsigned int _deltaTime, _lastFrame;

	GLfloat _xPos, _yPos, _lastX, _lastY;
	GLfloat _pitch, _yaw, _sensitivity;

	bool _keys[322], _firstMouse;

	GLfloat _cameraSpeed;

	void changeView(SDL_Event event);

};