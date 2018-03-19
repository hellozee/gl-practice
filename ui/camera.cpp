#include "camera.h"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, GLfloat fov, GLfloat ratio, GLfloat nearPlane, GLfloat farPlane):
cameraPos(cameraPos),_cameraFront(cameraFront),_cameraUp(cameraUp),_keys(322,false)
{
	_projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
	_cameraSpeed = 0.05f;
	_deltaTime = 0;
	_lastFrame = 0;
	_pitch = 0.0f ;
	_yaw = -90.0f;
	_firstMouse = true;
	_sensitivity = 0.1f;
    _xoffset = 0.0f;
    _yoffset = 0.0f;
    _out = false;
}

Camera::~Camera()
{

}

void Camera::Use(GLuint program)
{

	_view = glm::lookAt(cameraPos, cameraPos + _cameraFront, _cameraUp);

	GLint modelLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_view));

    modelLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_projection));

}

void Camera::manageEvents(SDL_Event event)
{
	if(event.type == SDL_KEYDOWN){
        _keys[event.key.keysym.sym] = true;
    }else if(event.type == SDL_KEYUP){
    	_keys[event.key.keysym.sym] = false;
    }

    if(event.type == SDL_MOUSEMOTION){
    	changeView(event);
    }
}

void Camera::doMovement(unsigned int currentFrame)
{
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	_cameraSpeed = (float) _deltaTime * 0.002;

	if(_keys[SDLK_w]){
		cameraPos += _cameraFront * _cameraSpeed;
	}

	if(_keys[SDLK_a]){
		cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
	}

	if(_keys[SDLK_s]){
		cameraPos -= _cameraFront * _cameraSpeed;
	}

	if(_keys[SDLK_d]){
		cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
	}

    SDL_Event emptyEvent;

    if(_out){
        changeView(emptyEvent);
    }

}

void Camera::changeView(SDL_Event event)
{
	_xPos = event.motion.x;
	_yPos = event.motion.y;

	if (_firstMouse)
    {
        _lastX = _xPos;
        _lastY = _yPos;
        _firstMouse = false;
    }

    if( _xPos == 800 || _xPos == 0 || _yPos == 600 || _yPos == 0){
        _out = true;
        return;
    }

    _xoffset = _xPos - _lastX;
    _yoffset = _lastY - _yPos;
    _xoffset *= _sensitivity;
    _yoffset *= _sensitivity;
    _out = false;

    _lastX = _xPos;
    _lastY = _yPos;

    _yaw   += _xoffset;
    _pitch += _yoffset;

    if (_pitch > 89.0f){
        _pitch = 89.0f;
    }

    if (_pitch < -89.0f){
        _pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    _cameraFront = glm::normalize(front);
}