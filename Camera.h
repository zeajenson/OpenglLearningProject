#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		this->perspective = glm::perspective(fov, aspect, zNear, zFar);
		this->position = pos;
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 getViewProjection() const {
		return this->perspective * glm::lookAt(this->position, this->position + this->forward, this->up);
	}

	~Camera() {};
private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

