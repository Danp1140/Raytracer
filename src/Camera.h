//
// Created by Daniel Paavola on 2020-12-11.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

class Camera{

private:
	glm::vec3 position;
	float fovy, theta, phi;
public:
	Camera();

	float getFovy(){return fovy;}

	glm::vec3 getPos(){return position;}

	void setPos(glm::vec3 p);

	void setFovy(float f);

	float getTheta(){return theta;}

	float getPhi(){return phi;}

	void setTheta(float t);

	void setPhi(float p);
};


#endif //RAYTRACING_CAMERA_H
