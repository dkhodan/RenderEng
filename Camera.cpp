#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	world_up = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movement_speed = startMoveSpeed;
	turn_speed = startTurnSpeed;

	update();
}

glm::vec3 Camera::GetCameraPosition()
{
	return position;
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::keys_control(bool* keys, GLfloat DeltaTime)
{
	GLfloat velocity = movement_speed * DeltaTime;

	if (keys[GLFW_KEY_W] == true)
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S] == true)
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A] == true)
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D] == true)
	{
		position += right * velocity;
	}
}

glm::mat4 Camera::calculate_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::mouse_control(GLfloat xChange, GLfloat yChange)
{
	xChange *= turn_speed;
	yChange *= turn_speed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

Camera::~Camera()
{
}
