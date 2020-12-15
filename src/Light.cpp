//
// Created by Daniel Paavola on 2020-12-12.
//

#include "Light.h"

Light::Light(){
	position=glm::vec3(1, 1, 1);
	intensity=1.0f;
}

Light::Light(glm::vec3 p) : position(p){
	intensity=1.25f;
}

void Light::setIntensity(float i){
	intensity=i;
}