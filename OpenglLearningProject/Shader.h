#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"


class Shader
{
public:
	Shader(std::string fileName);

	void bind();
	void update(const Transform& transfomr, const Camera& camera); //updates all uniforms in the array

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;
	enum {
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

