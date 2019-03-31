#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 init_pos, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat start_movement_speed, GLfloat start_turn_speed);
	~Camera();
	void keys_control(bool* keys, GLfloat DeltaTime);
	void mouse_control(GLfloat xChange, GLfloat yChange);
public:
	glm::mat4 calculate_view_matrix();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movement_speed;
	GLfloat turn_speed;

private:
	void update();
};

