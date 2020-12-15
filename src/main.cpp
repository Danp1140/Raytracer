

#include "Viewport.h"

int main(){

	Viewport::GLinit();
	Viewport v=Viewport();

	v.draw();

	do{
		v.draw();

		glfwSwapBuffers(v.getWindow());
		glfwPollEvents();
	}while(!glfwWindowShouldClose(v.getWindow())&&glfwGetKey(v.getWindow(), GLFW_KEY_ESCAPE)!=GLFW_PRESS);
	return 0;
}