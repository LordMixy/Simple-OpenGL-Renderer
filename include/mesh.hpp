#ifndef MESH_HPP
#define MESH_HPP

#include "../include/glad/glad.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace OpenGL
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoords;
	};

	struct Texture 
	{
		uint32_t id;
		std::string type;		
	};
	
	struct Mesh
	{
		std::vector<Vertex> vertices;			
		std::vector<uint32_t> indices;			
		std::vector<Texture> textures;			

		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			glGenVertexArrays(1, &vertexArray);
			glGenBuffers(1, &vertexBuffer);
			glGenBuffers(1, &indexBuffer);

			glBindVertexArray(vertexArray);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);			
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);			

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
			
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textureCoords));
						
			glBindVertexArray(0);
		}

		private: uint32_t vertexArray, vertexBuffer, indexBuffer;
	};
};

#endif
