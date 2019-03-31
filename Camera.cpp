#include "Camera.h"

Camera::Camera(glm::vec3 init_pos, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat start_movement_speed, GLfloat start_turn_speed)
{
	position = init_pos;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	this->movement_speed = start_movement_speed;
	this->turn_speed = start_turn_speed;
	update();
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::keys_control(bool* keys, GLfloat DeltaTime)
{
	GLfloat velocity = movement_speed * DeltaTime;
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
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
