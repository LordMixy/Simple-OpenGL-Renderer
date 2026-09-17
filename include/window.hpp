#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../include/backend.hpp"

#include <string>
#include <functional>

struct Window 
{
	BackendWindow* opaqueWindow;
	std::function<void(const double&, const double&)> mouseMoveCallback;
		
	Window(const int32_t& width, const int32_t& height, const std::string& title);

	float getDelta();
	
	void pollEvents() const;
	void makeCurrent() const;
	bool shouldClose() const;
	void activeMouseCallback() const;
	void setVsync(const bool& enable);
	bool isKeyPressed(const BackendKey& key) const;
	void terminate() const;

	private:
		float delta;
		float lastFrame;
};	

#endif
