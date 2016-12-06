#pragma once
#include <GL\glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string & fileName);

	void bind(unsigned int unit);

	~Texture();
private:

	GLuint texture;
};

