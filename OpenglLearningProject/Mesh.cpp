#include "Mesh.h"
#include <vector>



Mesh::Mesh(Vertex * vertices, unsigned int numVertices)
{
	this->drawCount = numVertices;

	glGenVertexArrays(1, &this->vertexArrayObject);
	glBindVertexArray(this->vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++) {
		positions.push_back(*(vertices[i].getPos()));
		texCoords.push_back(*(vertices[i].getTexCoord()));
	}

	glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffers); //generate a chunk of memory in the gpu to use
	glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 


	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 

	glBindVertexArray(0);

}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->vertexArrayObject);
}

void Mesh::draw() {
	glBindVertexArray(this->vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

	glBindVertexArray(0);
}