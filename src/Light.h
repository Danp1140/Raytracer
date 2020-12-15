//
// Created by Daniel Paavola on 2020-12-12.
//

#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

#include <glm/gtc/matrix_transform.hpp>

class Light{
private:
	glm::vec3 position;
	float intensity;
public:
	Light();

	Light(glm::vec3 p);

	glm::vec3 getPos(){return position;}

	float getIntensity(){return intensity;}

	void setIntensity(float i);
};


#endif //RAYTRACING_LIGHT_H
