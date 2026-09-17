#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../include/window.hpp"
#include <glm/glm.hpp>
#include <functional>

namespace OpenGL 
{	
	struct Camera 
	{	
		Window* parentWindow;
	
		glm::vec3 direction;	
		glm::vec3 position;	
		glm::vec3 worldUp;	
		glm::vec3 target;	
		glm::vec3 front;	
		glm::vec3 view;	
		glm::vec3 up;	

		float yaw;
		float lastX;
		float lastY;
		float pitch;	
		float speed;	
		float sensitivity;

		bool firstMouse;
		
		Camera(Window* parentWindow, const glm::vec3& startPosition);
				
		glm::mat4 getView();
		void handleKeyboardInput();
		void updateDirection();
		void mouseMoveCallback(const double& x, const double& y);
	};	
};

#endif // CAMERA_HPP
