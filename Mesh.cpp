#include "Mesh.h"
#include <iostream>
#include <vector>

Mesh::Mesh(const std::string fileName) 
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	initMesh(model);
}

Mesh::Mesh(Vertex * vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices)
{

	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++) {
		model.positions.push_back(*(vertices[i].getPos()));
		model.texCoords.push_back(*(vertices[i].getTexCoord()));
		model.normals.push_back(*(vertices[i].getNormal()));
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	this->initMesh(model);

	//this->drawCount = numVertices;
	//this->drawCount = numIndices;

	//glGenVertexArrays(1, &this->vertexArrayObject);
	//glBindVertexArray(this->vertexArrayObject);

	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texCoords;

	//positions.reserve(numVertices);
	//texCoords.reserve(numVertices);

	//for (unsigned int i = 0; i < numVertices; i++) {
	//	positions.push_back(*(vertices[i].getPos()));
	//	texCoords.push_back(*(vertices[i].getTexCoord()));
	//}

	//glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffers); //generate a chunk of memory in the gpu to use
	//glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory
	//
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 


	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 

	//glBindVertexArray(0);

}

void Mesh::initMesh(const IndexedModel & model) {
	
	this->drawCount = model.indices.size();

	glGenVertexArrays(1, &this->vertexArrayObject);
	glBindVertexArray(this->vertexArrayObject);

	//binding mesh position
	glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffers); //generate a chunk of memory in the gpu to use
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 

	//binding texture coordinatns
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw

	//binding normals
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);	//taking memory and moving it to gpu memory

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); //give opengl information on how to draw 


	glBindVertexArray(0);
	std::cout << "mesh initialized" << std::endl;
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->vertexArrayObject);
}

void Mesh::draw() {
	glBindVertexArray(this->vertexArrayObject);

//	glDrawArrays(GL_TRIANGLES, 0, this->drawCount);
	glDrawElements(GL_TRIANGLES, this->drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}