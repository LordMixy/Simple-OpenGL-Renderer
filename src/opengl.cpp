#include "../include/glad/glad.h"
#include "../include/opengl.hpp"

uint32_t OpenGL::loadShader(const std::string& shaderSource, uint32_t shaderType)
{
	uint32_t shader = glCreateShader(shaderType);
	const char* shaderSourceCstr = shaderSource.c_str();

	glShaderSource(shader, 1, &shaderSourceCstr, NULL);
	glCompileShader(shader);	

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{	
		char infoLog[512];
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);

		throw std::runtime_error(infoLog);
	}
	
	return shader;
}
