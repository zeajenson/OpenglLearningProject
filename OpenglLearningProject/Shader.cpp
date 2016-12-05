#include "Shader.h"
#include <fstream>
#include <string>


static std::string loadShader(std::string fileName);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char * errorMessage);
static GLuint createShader(const char * text, GLenum shaderType);

Shader::Shader(std::string fileName)
{
	std::string vertexShaderName = fileName;
	std::string fragmentShaderName = fileName;

	this->program = glCreateProgram();
	this->shaders[0] = createShader(loadShader(vertexShaderName.append(".vs")).c_str() , GL_VERTEX_SHADER);
	this->shaders[1] = createShader(loadShader(fragmentShaderName.append(".fs")).c_str() , GL_FRAGMENT_SHADER);

	for (unsigned int i = 0;i < NUM_SHADERS; i++)
		glAttachShader(this->program, this->shaders[i]);

	glBindAttribLocation(this->program, 0, "position"); //tells what opengl what part of shader program to read
	glBindAttribLocation(this->program, 1, "texCoord");

	glLinkProgram(this->program);
	checkShaderError(this->program,GL_LINK_STATUS, true, "error: program failed to link");

	glValidateProgram(this->program);
	checkShaderError(this->program, GL_LINK_STATUS, true, "error: program failed to validate");

	this->uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(this->program, this->shaders[i]);
		glDeleteShader(this->shaders[i]);
	}
	glDeleteProgram(this->program);
}

void Shader::bind() {
	glUseProgram(this->program);
}

void Shader::update(const Transform& transform, const Camera& camera) {
	glm::mat4 model = camera.getViewProjection() * transform.getModel(); //both are matracies that are added together through multiplying


	glUniformMatrix4fv(this->uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]); //transforms verticies using shaders
}

static GLuint createShader(const char * text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)std::cerr <<"error shader createoioiean faild" << std::endl;

	const GLchar * shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text;
	if(!text)
		shaderSourceStringLengths[0] = (sizeof(text)/sizeof(text[0]));


	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "error shader compilation failed");

	return shader;
} 

static std::string loadShader(std::string fileName) {
	std::string output;
	std::string line;
	std::ifstream file;
	file.open(fileName );

	std::cout << fileName << std::endl;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char * errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error<< "'" << std::endl;
	}
}