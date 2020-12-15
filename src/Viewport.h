//
// Created by Daniel Paavola on 2020-12-11.
//

#ifndef RAYTRACING_VIEWPORT_H
#define RAYTRACING_VIEWPORT_H

#include "Camera.h"
#include "Light.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

typedef struct{
	glm::vec3 vertices[3];
	glm::vec3 normal;
	glm::vec4 color;
	//make reflectivity a float and add w/ diffuse?
	bool reflective;
	float ior;
}face;

class Viewport{

private:
	GLFWwindow*window;
	Camera*c;
	std::vector<Light> lights;
	int width, height;
	int recursioncounter;
	double lmx, lmy;
	GLuint va, shaders, vertexbuffer, colorbuffer;
//	const int vres=3, hres=4;
//	const int vres=9, hres=14;
	const int vres=45, hres=72;
//	const int vres=90, hres=144;
//	const int vres=90, hres=90;
//	const int vres=900, hres=1440;
	//big nearclip, but proved my point for infinite mirror
//	const float nearclip=0.1f;
	//almost imperceptable @ 0.001, idk if works
	const float nearclip=0.001f;
	std::vector<face> faces;
	std::vector<glm::vec2> vertices;
	std::vector<std::vector<glm::vec4>> colorraster;

	glm::vec3 rayTriCollision(glm::vec3 o, glm::vec3 r, face f);

	glm::vec4 cast(glm::vec3 origin, glm::vec3 ray);

public:

	Viewport();

	static void GLinit();

	void draw();

	void render();

	GLFWwindow*getWindow(){return window;}

	static GLuint loadShaders(const char* vertex_shader_filepath, const char* fragment_shader_filepath);

	static bool loadOBJ(const char*obj_filepath, std::vector<face>&f);
};


#endif //RAYTRACING_VIEWPORT_H
