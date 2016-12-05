#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex {
public:
	Vertex(const glm::vec3 & pos,const glm::vec2 texCoord) {
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3 *getPos() {return &this->pos;}

	inline glm::vec2 *getTexCoord() {return &this->texCoord;}
protected:

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh(Vertex * vertices, unsigned int numVertices);

	virtual ~Mesh();

	void draw();

private:

	enum {
		POSITION_VB,
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;

};

