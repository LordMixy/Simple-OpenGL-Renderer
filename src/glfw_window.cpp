#include "../include/window.hpp"
#include "../include/utils.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

void onResize([[maybe_unused]] GLFWwindow* window, int32_t width, int32_t height)
{
	// TODO change window's height and width
	glViewport(0, 0, width, height);
}

Window::Window(const int32_t& width, const int32_t& height, const std::string& title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	opaqueWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (opaqueWindow == NULL)
	{
		log("Failed to initialize GLFWwindow", Utils::LogLevel::FATAL);
		throw std::runtime_error("Failed to initialize GLFWwindow");
	}
	glfwSetWindowUserPointer(opaqueWindow, this);

	makeCurrent();
	glfwSetFramebufferSizeCallback(opaqueWindow, onResize);	
}

void Window::makeCurrent() const
{
	glfwMakeContextCurrent(opaqueWindow);
}

void Window::setVsync(const bool& enable)
{
	glfwSwapInterval(!enable);
}

bool Window::shouldClose() const 
{
	return glfwWindowShouldClose(opaqueWindow);
}

void Window::activeMouseCallback() const
{
	log("Activating mouseCallback", Utils::LogLevel::DEBUG);
	glfwSetCursorPosCallback(opaqueWindow, 
		[] (auto glwindow, auto x, auto y) 
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));
			window->mouseMoveCallback(x, y);
		}
	);
}

void Window::pollEvents() const
{
	glfwSwapBuffers(opaqueWindow);
	glfwPollEvents();
}

bool Window::isKeyPressed(const BackendKey& key) const
{
	return glfwGetKey(opaqueWindow, key) == GLFW_PRESS;
}

float Window::getDelta()
{
	float frame = (float) glfwGetTime();
	delta = frame - lastFrame;
	lastFrame = frame;

	return delta;
}

void Window::terminate() const
{
	glfwTerminate();	
}
