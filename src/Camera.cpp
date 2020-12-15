//
// Created by Daniel Paavola on 2020-12-11.
//

#include "Camera.h"

Camera::Camera(){
	position=glm::vec3(1.5, 1.5, 2);
	theta=-0.75f;
	phi=0.5f;
	fovy=0.75f;
}

void Camera::setPos(glm::vec3 p){position=p;}

void Camera::setFovy(float f){fovy=f;}

void Camera::setTheta(float t){theta=t;}

void Camera::setPhi(float p){phi=p;}