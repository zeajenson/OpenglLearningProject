#pragma once
#define	_CRT_SECURE_NO_WARNINGS
#include <string>
#include "Shader.h"
#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "OutputTimer.h"


#ifdef main
#undef main
#endif

int main(int argc, char **  argv) {
	Display mainDisplay(700, 600, "hello world");
	Shader mainShader("./res/baseShader");
	Mesh stove("./res/monkey3.obj");
	Texture mainTexture("./res/Borked.jpg");
	Transform mainTransform;
	Camera mainCamera(glm::vec3(0, 0, -4), 70.0f, (float)mainDisplay.getWidth() / (float)mainDisplay.getHeight(), 0.01f, 10.0f);

	OutputTimer * mainOutputTimer = new OutputTimer();
	mainOutputTimer->startTimer();
	float refreshRate = 1000 / 24; //24 frames a sec
	float updateSpeed = 300;

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5,-0.5,0),	glm::vec2(0,0)),
							Vertex(glm::vec3(0,0.5,0.5),		glm::vec2(0.5,1)),
							Vertex(glm::vec3(0.5,-0.5,0),	glm::vec2(1,0)),
							Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)),
							Vertex(glm::vec3(0,0.5,0.5), glm::vec2(0.5,1.0)),
							Vertex(glm::vec3(0.5,-0.5,0.5), glm::vec2(1.0,0.0)) };
	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	float counter = 0.1f;

	while (!mainDisplay.isClosed()) 
	{
		if (mainOutputTimer->getElapsedTime() >= (refreshRate)) {
			mainDisplay.clear(0.0f, 0.0f, 1.0f, 0.0f);

			mainTransform.getPos().x = (sinf(counter / 2) / 2);
			mainTransform.getPos().y = (cosf(counter / 2) / 2);
			mainTransform.getRot().x = (counter);
			mainTransform.getRot().y = (sinf(counter) /2);
			mainTransform.getRot().z = (cosf(counter) / 2);

			//		mainTransform.getRot().x = (counter +3);

			mainTexture.bind(1);
			mainShader.update(mainTransform, mainCamera);
			mainShader.bind();
			mesh.draw();
			stove.draw();
			//		otherMesh.draw();

			mainDisplay.update();

			counter += (float)(refreshRate/ updateSpeed);
			mainOutputTimer->resetTimer();
		}
	}


	return 0;
}

