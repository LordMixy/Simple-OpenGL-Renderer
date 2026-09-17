#include "../include/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CAMERA_DEFAULT_SENSITIVITY 0.1f
#define CAMERA_DEFAULT_SPEED 2.5f
#define CAMERA_DEFAULT_YAW -90.0f
#define CAMERA_DEFAULT_PITCH 0.0f

using OpenGL::Camera;
		
Camera::Camera(Window* parentWindow, const glm::vec3& startPosition)
{
	firstMouse = true;

	position = startPosition;
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	yaw = CAMERA_DEFAULT_YAW;
	pitch = CAMERA_DEFAULT_PITCH;
	speed = CAMERA_DEFAULT_SPEED;
	sensitivity = CAMERA_DEFAULT_SENSITIVITY;

	this->parentWindow = parentWindow;
	updateDirection();
}
		
glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::updateDirection()
{
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Camera::handleKeyboardInput()
{
	float velocity = speed * parentWindow->getDelta();
	if (parentWindow->isKeyPressed(BK_KEY_W))
	{
		position += front * velocity;
	}
	if (parentWindow->isKeyPressed(BK_KEY_A))
	{
		position -= glm::normalize(glm::cross(front, up)) * velocity;
	}
	if (parentWindow->isKeyPressed(BK_KEY_S))
	{
		position -= front * velocity;
	}
	if (parentWindow->isKeyPressed(BK_KEY_D))
	{
		position += glm::normalize(glm::cross(front, up)) * velocity;
	}
}

void Camera::mouseMoveCallback(const double& x, const double& y)
{
	if (firstMouse)
	{
	    lastX = x;
	    lastY = y;
	    firstMouse = false;
	}

	double xDiff = x - lastX;
	double yDiff = lastY - y;
	lastX = x;
	lastY = y;

	xDiff *= sensitivity;
	yDiff *= sensitivity;

	yaw += xDiff;
	pitch += yDiff;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateDirection();
	front = glm::normalize(direction);
}
