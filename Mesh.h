#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "OBJ_Loader.h"

class Vertex {
public:
	Vertex(const glm::vec3 & pos,const glm::vec2 texCoord, const glm::vec3 normal = glm::vec3(0,0,0)) {
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3 *getPos() {return &this->pos;}

	inline glm::vec2 *getTexCoord() {return &this->texCoord;}
	inline glm::vec3 *getNormal() { return &this->normal; }
protected:

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(Vertex * vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices);
	Mesh::Mesh(const std::string fileName);

	virtual ~Mesh();

	void draw();

private:

	void initMesh(const IndexedModel & model);

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;

};

