#include "../include/glad/glad.h"
#include "../include/utils.hpp"
#include "../include/opengl.hpp"
#include "../include/window.hpp"
#include "../include/camera.hpp"
#include "../include/program.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <vector>

#define W 1600
#define H 900

using namespace Utils;

int main()
{
	Window window { W, H, "ciao" };
	window.setVsync(true);

	OpenGL::Camera camera { &window, glm::vec3(0.0f, 0.0f, 3.0f) };

	window.mouseMoveCallback = std::bind(
		&OpenGL::Camera::mouseMoveCallback, 
		&camera, 
		std::placeholders::_1, 
		std::placeholders::_2
	);
	window.activeMouseCallback();	
	
	GLFWwindow* bkWindow = window.opaqueWindow;
	glfwSetInputMode(bkWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		log("Failed to initialize GLAD", LogLevel::FATAL);
	    return EXIT_FAILURE;
	}  

	glEnable(GL_DEPTH_TEST);  
	
	std::vector<float> vertices 
	{ 
	    -0.5f, -0.5f, -0.5f, 
	     0.5f, -0.5f, -0.5f, 
	     0.5f,  0.5f, -0.5f,  
	     0.5f,  0.5f, -0.5f, 
	    -0.5f,  0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f,  

	    -0.5f, -0.5f,  0.5f,  
	     0.5f, -0.5f,  0.5f,  
	     0.5f,  0.5f,  0.5f, 
	     0.5f,  0.5f,  0.5f, 
	    -0.5f,  0.5f,  0.5f,  
	    -0.5f, -0.5f,  0.5f,  

	    -0.5f,  0.5f,  0.5f, 
	    -0.5f,  0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    -0.5f, -0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f, 

	     0.5f,  0.5f,  0.5f, 
	     0.5f,  0.5f, -0.5f,  
	     0.5f, -0.5f, -0.5f, 
	     0.5f, -0.5f, -0.5f, 
	     0.5f, -0.5f,  0.5f, 
	     0.5f,  0.5f,  0.5f,  

	    -0.5f, -0.5f, -0.5f,  
	     0.5f, -0.5f, -0.5f,  
	     0.5f, -0.5f,  0.5f, 
	     0.5f, -0.5f,  0.5f,  
	    -0.5f, -0.5f,  0.5f,  
	    -0.5f, -0.5f, -0.5f, 

	    -0.5f,  0.5f, -0.5f, 
	     0.5f,  0.5f, -0.5f,  
	     0.5f,  0.5f,  0.5f,  
	     0.5f,  0.5f,  0.5f,  
	    -0.5f,  0.5f,  0.5f,  
	    -0.5f,  0.5f, -0.5f,  
	};

	OpenGL::Program cubeProgram;
	try 
	{
		cubeProgram = OpenGL::Program("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
	} 
	catch (const std::runtime_error& error) 
	{
		log(std::string("glProgram Exception: ") + error.what(), LogLevel::FATAL);
		return EXIT_FAILURE;
	}

	uint32_t vao;
	glGenVertexArrays(1, &vao);  
	glBindVertexArray(vao);
	
	uint32_t buffer;	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);	 
	glEnableVertexAttribArray(0);

	glm::mat4 model, view, projection;
	projection = glm::perspective(glm::radians(45.0f), (float) W / (float) H, 0.1f, 100.0f);

	while(!window.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.handleKeyboardInput();
		view = camera.getView();

		//
		
		glUseProgram(cubeProgram.id);

		model = glm::mat4(1.0f);
		cubeProgram.uniform3fv("objectColor", glm::vec3 { 1.0, 0.5, 0.31 });

		cubeProgram.uniformMatrix4fv("model", model);
		cubeProgram.uniformMatrix4fv("view", view);
		cubeProgram.uniformMatrix4fv("projection", projection);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//

		window.pollEvents(); 
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &buffer);
	glDeleteProgram(cubeProgram.id);
	
	window.terminate();
	return EXIT_SUCCESS;
}
