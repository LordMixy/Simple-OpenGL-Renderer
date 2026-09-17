#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP

#include "../include/glad/glad.h"
#include "../include/utils.hpp"
#include "../include/opengl.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace OpenGL
{
	struct Program
	{
		uint32_t id;

		Program(const std::string& vsFilename, const std::string& fsFilename)
		{
			std::string vsSource = Utils::readFileContent(vsFilename);
			std::string fsSource = Utils::readFileContent(fsFilename);

			uint32_t vertexShader = loadShader(vsSource, GL_VERTEX_SHADER);
			Utils::log(vsFilename + ": Vertex Shader OK", Utils::LogLevel::DEBUG);

			uint32_t fragmentShader = loadShader(fsSource, GL_FRAGMENT_SHADER);
			Utils::log(fsFilename + ": Fragment Shader OK", Utils::LogLevel::DEBUG);

			id = glCreateProgram();
			glAttachShader(id, vertexShader);
			glAttachShader(id, fragmentShader);
			glLinkProgram(id);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void uniformMatrix4fv(const std::string& location, const glm::mat4& matrix)
		{
			glUniformMatrix4fv(glGetUniformLocation(id, location.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}		

		void uniform3fv(const std::string& location, const glm::vec3& vektor)
		{
			glUniform3fv(glGetUniformLocation(id, location.c_str()), 1, glm::value_ptr(vektor));
		}
		
		Program() = default;
	};
};

#endif
