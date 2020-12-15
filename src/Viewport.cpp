//
// Created by Daniel Paavola on 2020-12-11.
//

#include "Viewport.h"

Viewport::Viewport(){
	const GLFWvidmode*mode=glfwGetVideoMode(glfwGetPrimaryMonitor());
	window=glfwCreateWindow(mode->width, mode->height, "Raytracing", nullptr,
	                                   nullptr);
	width=mode->width;
	height=mode->height;
	if(window==nullptr){
		std::cout<<"Window Failure ("<<stderr<<")\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if(glewInit()!=GLEW_OK){
		std::cout<<"GLEW Failure ("<<stderr<<")\n";
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	c=new Camera();
	lights.push_back(Light(glm::vec3(2, 2, 2)));
	lights.push_back(Light(glm::vec3(0, 2, 0)));

	recursioncounter=0;

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

//	loadOBJ("../resources/objs/suzanne.obj", faces);//967 tris
	loadOBJ("../resources/objs/icosphere.obj", faces);//20 tris
//	loadOBJ("../resources/objs/hiresicosphere.obj", faces);//320 tris
//	loadOBJ("../resources/objs/cup.obj", faces);//34 tris

	//refraction scene:
//	faces.push_back({{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)}, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), false, 1.333f});
////	faces.push_back({{glm::vec3(0, 0, 0), glm::vec3(0, 0.25, 0), glm::vec3(-10, 0, 10)}, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), false, 0.0f});
////	faces.push_back({{glm::vec3(-10, 0.25, 10), glm::vec3(0, 0.25, 0), glm::vec3(-10, 0, 10)}, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), false, 0.0f});
//	for(float x=-3.0f;x<3.25f;x+=0.25f){
//		faces.push_back({{glm::vec3(x, 0, 10), glm::vec3(x+0.25f, 0, 10), glm::vec3(x+0.25f, 0, -10)}, glm::vec3(0, 1, 0), glm::vec4(1, x, 1, 1), false, 0.0f});
//		faces.push_back({{glm::vec3(x, 0, -10), glm::vec3(x+0.25f, 0, 10), glm::vec3(x+0.25f, 0, -10)}, glm::vec3(0, 1, 0), glm::vec4(1, x, 1, 1), false, 0.0f});
//	}


	//more than one reflected face causes issues
	//1st face gets precedence
//	faces.push_back({{glm::vec3(0.5, 0.25, 0.5), glm::vec3(0.5, 0.5, 0.25), glm::vec3(0.25, 0.5, 0.5)}, glm::vec3(0, 1, 0), glm::vec4(0, 0, 0, 1), false, 1.5f});
//	faces.push_back({{glm::vec3(0.25, 0.5, 0.25), glm::vec3(0.5, 0.5, 0.25), glm::vec3(0.25, 0.5, 0.5)}, glm::vec3(0, 1, 0), glm::vec4(0, 0, 0, 1), false, 1.5f});
//	faces.push_back({{glm::vec3(0.5, 0.25, 0.5), glm::vec3(0.5, 0.5, 0.25), glm::vec3(0.25, 0.5, 0.5)}, glm::vec3(0, 1, 0), glm::vec4(0, 0, 0, 1), true, 0.0f});
//	faces.push_back({{glm::vec3(0.25, 0.5, 0.25), glm::vec3(0.5, 0.5, 0.25), glm::vec3(0.25, 0.5, 0.5)}, glm::vec3(0, 1, 0), glm::vec4(0, 0, 0, 1), true, 0.0f});


	faces.push_back({{glm::vec3(0, 0, 0), glm::vec3(0, 0, 2), glm::vec3(2, 0, 0)}, glm::vec3(0, 0, 0), glm::vec4(0, 0, 1, 1), false, 0.0f});
	faces.push_back({{glm::vec3(2, 0, 2), glm::vec3(0, 0, 2), glm::vec3(2, 0, 0)}, glm::vec3(0, 0, 0), glm::vec4(0, 0, 1, 1), false, 0.0f});
	faces.push_back({{glm::vec3(0, 0, 0), glm::vec3(2, 0, 0), glm::vec3(0, 2, 0)}, glm::vec3(0, 0, 0), glm::vec4(0, 1, 0, 1), false, 0.0f});
	faces.push_back({{glm::vec3(0, 0, 0), glm::vec3(0, 2, 0), glm::vec3(0, 0, 2)}, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), false, 0.0f});
//	//this one below aint quite right
////	faces.push_back({{glm::vec3(0, 0, 0), glm::vec3(0, 2, 0), glm::vec3(0, 0, 2)}, glm::vec3(0, 0, 0), glm::vec4(0, 0, 0, 1), true, 0.0f});
	faces.push_back({{glm::vec3(0, 2, 0), glm::vec3(2, 2, 0), glm::vec3(2, 0, 0)}, glm::vec3(0, 0, 0), glm::vec4(1, 0, 1, 1), false, 0.0f});
	faces.push_back({{glm::vec3(2, 0, 2), glm::vec3(2, 2, 2), glm::vec3(2, 0, 0)}, glm::vec3(0, 0, 0), glm::vec4(1, 1, 0, 1), false, 0.0f});
	faces.push_back({{glm::vec3(2, 0, 2), glm::vec3(2, 2, 2), glm::vec3(0, 0, 2)}, glm::vec3(0, 0, 0), glm::vec4(0, 1, 1, 1), false, 0.0f});
	faces.push_back({{glm::vec3(0, 2, 0), glm::vec3(0, 0, 2), glm::vec3(0, 2, 2)}, glm::vec3(0, 0, 0), glm::vec4(1, 0, 0, 1), false, 0.0f});



	//vertex order matters and is not arbitrary

	for(auto&f:faces) f.normal=glm::normalize(glm::cross(f.vertices[1]-f.vertices[0], f.vertices[2]-f.vertices[0]));

	colorraster=std::vector<std::vector<glm::vec4>>(hres);
	for(int x=0;x<hres;x++){
		colorraster[x]=std::vector<glm::vec4>(vres);
		for(int y=0;y<vres;y++) colorraster[x][y]=glm::vec4(0.1, 0.1, 0.1, 1);
	}

	glfwGetCursorPos(window, &lmx, &lmy);

	shaders=loadShaders("../resources/shaders/VertexShader.glsl", "../resources/shaders/FragmentShader.glsl");

	for(int x=0;x<hres;x++){
		for(int y=0;y<vres;y++){
			vertices.emplace_back(x*width/hres, y*height/vres);
			vertices.emplace_back((x+1)*width/hres, y*height/vres);
			vertices.emplace_back((x+1)*width/hres, (y+1)*height/vres);

			vertices.emplace_back(x*width/hres, y*height/vres);
			vertices.emplace_back(x*width/hres, (y+1)*height/vres);
			vertices.emplace_back((x+1)*width/hres, (y+1)*height/vres);
		}
	}
	for(int x=0;x<vertices.size();x++){
		vertices[x]=glm::vec2(vertices[x].x/width*2-1, vertices[x].y/height*2-1);
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

}

void Viewport::GLinit(){
	if(!glfwInit()){
		std::cout<<"GLFW Failure ("<<stderr<<")\n";
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void Viewport::draw(){
	if(glfwGetKey(window, GLFW_KEY_SPACE)) c->setPos(c->getPos()+glm::vec3(0, 0.05, 0));
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) c->setPos(c->getPos()+glm::vec3(0, -0.05, 0));
	if(glfwGetKey(window, GLFW_KEY_D)) c->setPos(c->getPos()+glm::vec3(0.05, 0, 0));
	if(glfwGetKey(window, GLFW_KEY_A)) c->setPos(c->getPos()+glm::vec3(-0.05, 0, 0));
	if(glfwGetKey(window, GLFW_KEY_S)) c->setPos(c->getPos()+glm::vec3(0, 0, 0.05));
	if(glfwGetKey(window, GLFW_KEY_W)) c->setPos(c->getPos()+glm::vec3(0, 0, -0.05));
//	std::cout<<c->getPos().x<<", "<<c->getPos().y<<", "<<c->getPos().z<<std::endl;

	if(glfwGetKey(window, GLFW_KEY_UP)) faces[1].vertices[0].y+=0.05;
	if(glfwGetKey(window, GLFW_KEY_DOWN)) faces[1].vertices[0].y-=0.05;
	if(glfwGetKey(window, GLFW_KEY_RIGHT)) faces[1].vertices[0].x+=0.05;
	if(glfwGetKey(window, GLFW_KEY_LEFT)) faces[1].vertices[0].x-=0.05;
	if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) faces[1].vertices[0].z+=0.05;
	if(glfwGetKey(window, GLFW_KEY_SLASH)) faces[1].vertices[0].z-=0.05;
	//below normal calculation is what allows first face to function
	//normalization is important as well
//	faces[1].normal=glm::cross(faces[1].vertices[1]-faces[1].vertices[0], faces[1].vertices[2]-faces[1].vertices[1]);
	faces[1].normal=glm::normalize(glm::cross(faces[1].vertices[1]-faces[1].vertices[0], faces[1].vertices[2]-faces[1].vertices[0]));
//	faces[1].normal=glm::normalize(glm::cross(faces[0].vertices[1]-faces[0].vertices[0], faces[0].vertices[2]-faces[0].vertices[0]));
//	f.normal=glm::cross(f.vertices[1]-f.vertices[0], f.vertices[2]-f.vertices[1])
//	std::cout<<faces[0].vertices[2].x<<", "<<faces[0].vertices[2].y<<", "<<faces[0].vertices[2].z<<std::endl;

	if(glfwGetKey(window, GLFW_KEY_PERIOD)) lights[0].setIntensity(lights[0].getIntensity()+0.1);
	if(glfwGetKey(window, GLFW_KEY_COMMA)) lights[0].setIntensity(lights[0].getIntensity()-0.1);

	if(glfwGetKey(window, GLFW_KEY_9)) c->setFovy(c->getFovy()+0.01);
	if(glfwGetKey(window, GLFW_KEY_0)) c->setFovy(c->getFovy()-0.01);

	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	c->setTheta(c->getTheta()-(lmx-mx)*0.005);
	c->setPhi(c->getPhi()-(lmy-my)*0.005);
	lmx=mx; lmy=my;

	std::chrono::high_resolution_clock::time_point start=std::chrono::high_resolution_clock::now();

	render();

	std::cout<<"render finished!\ntook "<<(std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now()-start)).count()<<"seconds"<<std::endl;

	std::vector<glm::vec4> colors;
	for(int x=0;x<hres;x++){
		for(int y=0;y<vres;y++){
			colors.emplace_back(colorraster[x][y]);
			colors.emplace_back(colorraster[x][y]);
			colors.emplace_back(colorraster[x][y]);
			colors.emplace_back(colorraster[x][y]);
			colors.emplace_back(colorraster[x][y]);
			colors.emplace_back(colorraster[x][y]);
		}
	}

	glUseProgram(shaders);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
//	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteBuffers(1, &colorbuffer);
}

void Viewport::render(){
	glm::vec3 tempcollision, firstcollision;
	glm::vec4 color;
	for(int x=0;x<hres;x++){
		for(int y=0;y<vres;y++){
//			glm::vec3 temp=glm::normalize(glm::vec3(
//					2.0f*(1.0f/(2.0f*(float)hres)+(float)x/(float)hres)-1.0f,
//					2.0f*(1.0f/(2.0f*(float)vres)+(float)y/(float)vres)-1.0f,
//					-1.0f/tan(c->getFovy()/2.0f)));
			//below is experimental scaling to reduce stretch
			glm::vec3 temp=glm::normalize(glm::vec3(
					((float)width/(float)height)*2.0f*(1.0f/(2.0f*(float)hres)+(float)x/(float)hres)-1.0f,
					2.0f*(1.0f/(2.0f*(float)vres)+(float)y/(float)vres)-1.0f,
					-1.0f/tan(c->getFovy()/2.0f)));

			glm::mat3x3 mat=glm::mat3x3();
			mat[0][0]=1;
			mat[0][1]=0;
			mat[0][2]=0;
			mat[1][0]=0;
			mat[1][1]=cos(c->getPhi());
			mat[1][2]=-sin(c->getPhi());
			mat[2][0]=0;
			mat[2][1]=sin(c->getPhi());
			mat[2][2]=cos(c->getPhi());
			glm::mat3x3 yrot=glm::mat3x3();
			yrot[0][0]=cos(c->getTheta());
			yrot[0][1]=0;
			yrot[0][2]=sin(c->getTheta());
			yrot[1][0]=0;
			yrot[1][1]=1;
			yrot[1][2]=0;
			yrot[2][0]=-sin(c->getTheta());
			yrot[2][1]=0;
			yrot[2][2]=cos(c->getTheta());
			recursioncounter=0;
			colorraster[x][y]=cast(c->getPos(), yrot*(mat*temp));
			//this print REALLY screws efficiency
//			std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<(float)x/(float)hres<<" "<<(float)y/(float)hres;

		}
//		std::cout<<x<<std::endl;
	}
}

glm::vec3 Viewport::rayTriCollision(glm::vec3 o, glm::vec3 r, face f){
	float t=-(glm::dot(f.normal, o)-glm::dot(f.normal, f.vertices[0]))/glm::dot(f.normal, glm::normalize(r));
	if(t<nearclip) return o;
	glm::vec3 P=o+t*glm::normalize(r);

//	glm::vec3 edgetests[3];
//	edgetests[0]=glm::cross(f.vertices[1]-f.vertices[0], P-f.vertices[0]);
//	edgetests[1]=glm::cross(f.vertices[2]-f.vertices[1], P-f.vertices[1]);
//	edgetests[2]=glm::cross(f.vertices[0]-f.vertices[2], P-f.vertices[2]);
//
//	if(glm::dot(f.normal, edgetests[0])>0
//	   &&glm::dot(f.normal, edgetests[1])>0
//	   &&glm::dot(f.normal, edgetests[2])>0){
//		return P;
//	}
	//unsure if below has better performance than above, check later
	if(glm::dot(f.normal, glm::cross(f.vertices[1]-f.vertices[0], P-f.vertices[0]))>0
	&&glm::dot(f.normal, glm::cross(f.vertices[2]-f.vertices[1], P-f.vertices[1]))>0
	&&glm::dot(f.normal, glm::cross(f.vertices[0]-f.vertices[2], P-f.vertices[0]))>0){
		return P;
	}
	//unsure of what to return if no collision
	//for now, returning origin, as it is where collision behaves oddly anyways
	return o;
}

	/*
	 * K, so this was a quick test to see if my intensity algorithm worked, and it was surprisingly effective.
	 * The next step is to integrate a check for whether or not the ray from the collision to the light intersects
	 * any other planes. This will involve some restructuring of the object-oriented parts of this code, specifically
	 * with regards to functions. It would likely be prudent to add a collision function (which would return a point
	 * of collision between a ray and tri. Additionally, it should be noted that diffraction, deflection, and diffusion
	 * are all enhanced with more than one ray bounce. Therefore, after implementing a collision function, as well as
	 * maybe tidying up the render function so it is usable, it would probably be a good call to allow recursion or
	 * some other manner of multiple ray bounces. Perhaps add diffuse, reflect, IOR, etc. values to the face struct.
	 * NOTE: I don't think recursion is necessary if we want to cap the number of casts. Diffusion happens on first
	 * cast/collision, reflection and defraction can each be their own additional casts which are limited to only being
	 * affected by diffusion. Simpler, although a bit less effective.
	 */

glm::vec4 Viewport::cast(glm::vec3 origin, glm::vec3 ray){
	recursioncounter++;
	glm::vec3 tempcollision, firstcollision;
	float mindistance=9999, templen=0;
	face*collided;
	bool skip;
	glm::vec4 color;
	//ambient lighting below
	color=glm::vec4(0, 0, 0, 1);
	collided=nullptr;
	for(auto& i:faces){
		tempcollision=rayTriCollision(origin, ray, i);
		if(tempcollision==origin) continue;
		templen=glm::length(tempcollision-origin);
		if(templen<mindistance){
			mindistance=templen;
			firstcollision=tempcollision;
			collided=&i;
		}

	}

	if(collided!=nullptr){
		for(auto&l:lights){
			skip=false;
			for(auto&j:faces){
				//not checking collided!=&j causes prohibitive noise
				//ruling out shadows from transmission planes is ham-fisted
//				if(collided!=&j&&j.ior==0.0f&&rayTriCollision(firstcollision, l.getPos()-firstcollision, j)!=firstcollision){
				if(collided!=&j&&rayTriCollision(firstcollision, l.getPos()-firstcollision, j)!=firstcollision){
					skip=true;
					break;
				}
			}
			if(skip) continue;
			if(collided->ior>0){
				//should refraction deflect as well?

				//should figure system for determining original ior, allowing for thicker materials????
				if(recursioncounter<10){
					float costhetai=glm::dot(glm::normalize(ray), glm::normalize(collided->normal));

					//may have to negate ray here and/or above
					//do refraction inverse when normal is on wrong side?
//				return cast(firstcollision, ray*(1.0f/collided->ior)+(float)((1.0f/collided->ior)*costhetai-sqrt(1-((pow(1.0f/collided->ior, 2)*(1-pow(costhetai, 2))))))*collided->normal);
					//keep from self-reflection?
					color+=cast(firstcollision, ray*(1.0f/collided->ior)+
					(float)((1.0f/collided->ior)*costhetai-sqrt(1.0f-((pow(1.0f/collided->ior,2)*(1.0f-pow(costhetai,2))))))*collided->normal);
//				return cast((1.0f/collided->ior*ray)+(float)(1.0f/collided->ior*-glm::dot(collided->normal, ray)-sqrt(1.0f-pow(1.0f/collided->ior, 2)*(1.0f-pow(glm::dot(collided->normal, ray), 2))))*collided->normal);
					//c2 = sqrt( 1 - n^2 * (1 - c1^2) )
					//Rr = (n * V) + (n * c1 - c2) * N
				}
				else std::cout<<"problematic number of refractions"<<std::endl;
			}
			if(collided->reflective){
				//odd behavior when D!=0...dissapearings and crashes from recursion
				//could install max bounce, but that should also be moderated by scene setting...
				//should also find out why a single reflective face is getting infinite recursion
//				std::cout<<collided->normal.x<<", "<<collided->normal.y<<", "<<collided->normal.z<<std::endl;
//				return cast(firstcollision, ray-2.0f*collided->normal*glm::dot(collided->normal, ray));
//				std::cout<<collided->normal.x<<", "<<collided->normal.y<<", "<<collided->normal.z<<std::endl;
//				color+=cast(firstcollision, ray-2.0f*collided->normal*glm::dot(collided->normal, ray));
//				std::cout<<recursioncounter<<std::endl;
//				color+=cast(firstcollision, glm::normalize(ray-2.0f*collided->normal*glm::dot(collided->normal, ray)));
				if(recursioncounter<10){
					//plain return here makes misbehaving faces disappear
					//using = instead of += has same effect
					//when they're visible and "transparent," maybe they're just getting some extra brightness
					//sure as hell not getting refracted
					//second face is getting to a "problematic number of reflections"
					//raising the limit till it doesn't happen doesn't solve the problem
					//since returning or equaling disappears face, it can be inferred that brightness increase is due to
					//diffuse at end
					//therefore, this part is just returning a through vector
					color+=cast(firstcollision, glm::normalize(ray-2.0f*collided->normal*glm::dot(collided->normal, ray)));
//					return cast(firstcollision, glm::normalize(ray-2.0f*collided->normal*glm::dot(collided->normal, ray)));
				}
				else std::cout<<"problematic number of reflections"<<std::endl;
//				color+=cast(firstcollision, glm::normalize(ray)-2.0f*glm::normalize(collided->normal)*glm::dot(glm::normalize(collided->normal), glm::normalize(ray)));

//				color+=cast(firstcollision, ray-2.0f*glm::normalize(collided->normal)*glm::dot(glm::normalize(collided->normal), ray));
//				return cast(glm::normalize(ray)-2.0f*glm::normalize(collided->normal)*glm::dot(glm::normalize(collided->normal), glm::normalize(ray)));
			}
			//light incidence system below recommended by website, but found unpractical, personally
//			lightincidence=glm::dot(l.getPos(), collided->normal);
//			if(lightincidence<0) lightincidence=0;
			color+=collided->color*(float)(l.getIntensity()/(1+pow(glm::length(l.getPos()-firstcollision), 2)));
		}
	}

	return color;
}

GLuint Viewport::loadShaders(const char*vertex_shader_filepath, const char*fragment_shader_filepath){
	GLuint VertexShaderID=glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_filepath, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr<<VertexShaderStream.rdbuf();
		VertexShaderCode=sstr.str();
		VertexShaderStream.close();
	}else{
		std::cout<<"Vertex Shader File Initialization Failure ("<<vertex_shader_filepath<<")\n";
		getchar();
		return 0;
	}
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_filepath, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr<<FragmentShaderStream.rdbuf();
		FragmentShaderCode=sstr.str();
		FragmentShaderStream.close();
	}
	GLint Result=GL_FALSE;
	int InfoLogLength;
	const char*VertexSourcePointer=VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		std::cout<<&VertexShaderErrorMessage[0]<<'\n';
	}
	const char*FragmentSourcePointer=FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		std::cout<<&FragmentShaderErrorMessage[0]<<'\n';
	}
	GLuint ProgramID=glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		std::cout<<&ProgramErrorMessage[0]<<'\n';
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}

bool Viewport::loadOBJ(const char*obj_filepath, std::vector<face>&f){
	std::vector<unsigned int> vertIndicies, normIndicies;
	std::vector<glm::vec3> verttemps, normtemps;
	FILE*file=fopen(obj_filepath, "r");
	if(file==nullptr){
		std::cout<<"Loading OBJ Failure ("<<obj_filepath<<")\n";
		return false;
	}
	while(true){
		char lineheader[1024];//128?
		int res=fscanf(file, "%s", lineheader);
		if(res==EOF){break;}
		if(strcmp(lineheader, "v")==0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			verttemps.push_back(vertex);
		}else if(strcmp(lineheader, "vn")==0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normtemps.push_back(normal);
		}else if(strcmp(lineheader, "f")==0){
			std::string vert1, vert2, vert3;
			unsigned int vertidx[3], normidx[3];
			int matches=fscanf(file, "%d//%d %d//%d %d//%d", &vertidx[0], &normidx[0], &vertidx[1], &normidx[1],
			                   &vertidx[2], &normidx[2]);
			if(matches!=6){
				std::cout<<"OBJ Format Failure ("<<obj_filepath<<"), remember not to include UV maps)\n";
				return false;
			}
			vertIndicies.push_back(vertidx[0]);
			vertIndicies.push_back(vertidx[1]);
			vertIndicies.push_back(vertidx[2]);
			normIndicies.push_back(normidx[0]);
			normIndicies.push_back(normidx[1]);
			normIndicies.push_back(normidx[2]);
		}
	}
//	std::cout<<"Vertex Indicies: "<<vertIndicies.size()<<'\n';
	for(unsigned int x=0;x<vertIndicies.size();x+=3){
		//below scaling & translation is temporary
		f.push_back({{0.2f*verttemps[vertIndicies[x]-1]+4.0f*glm::vec3(0.25, 0.25, 0.25),
			   0.2f*verttemps[vertIndicies[x+1]-1]+4.0f*glm::vec3(0.25, 0.25, 0.25),
			   0.2f*verttemps[vertIndicies[x+2]-1]+4.0f*glm::vec3(0.25, 0.25, 0.25)},
			   glm::vec3(0, 0, 0),
			   glm::vec4(0.5, 0.5, 0.5, 1), false, 1.25f});
//			   glm::vec4(1, 1, 1, 1), false, 0.0f});
//		vertices.push_back(verttemps[vertIndicies[x]-1]);
//		std::cout<<"Vertex "<<x<<": "<<verttemps[vertIndicies[x]-1].x<<", "<<verttemps[vertIndicies[x]-1].y<<", "<<verttemps[vertIndicies[x]-1].z<<"\n";
	}
//	std::cout<<"Normal Indicies: "<<normIndicies.size()<<'\n';
	for(unsigned int x=0;x<normIndicies.size();x+=3){
//		normals.push_back(normtemps[normIndicies[x]-1]);
		//for now just takes the norm of the first vertex
//		f[x/3].normal=(normtemps[normIndicies[x]-1]);
		f[x/3].normal=glm::normalize(glm::cross(f[x/3].vertices[1]-f[x/3].vertices[0], f[x/3].vertices[2]-f[x/3].vertices[0]));
//		f[x].normal=(normtemps[normIndicies[x]-1]+normtemps[normIndicies[x+1]-1]+normtemps[normIndicies[x+2]-1])/3.0f;
//		std::cout<<"Normal "<<x<<": "<<normtemps[normIndicies[x]-1].x<<", "<<normtemps[normIndicies[x]-1].y<<", "<<normtemps[normIndicies[x]-1].z<<"\n";
	}
	return true;
}