#include "window.h"
#include <iostream>
#include <vector>

namespace fs {
	namespace window {

		Window::Window(const char* name, int width, int height) {
			m_Name = name;
			m_Width = width;
			m_Height = height;
			m_Keyboard;
			m_Mouse;
			if (!init()) {
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initiate glfw" << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
			if (!m_Window) {
				glfwTerminate();
				std::cout << "Failed to create Window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSwapInterval(0);
			glfwSetFramebufferSizeCallback(m_Window, onWindowResize);
			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW" << std::endl;
			}
			std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetKeyCallback(m_Window, onKeyChange);
			glfwSetMouseButtonCallback(m_Window, onMouseChange);
			glfwSetCursorPosCallback(m_Window, onMouseMove);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glEnable(GL_DEBUG_OUTPUT);
			
			return true;
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::clear() const {
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		void Window::update() {
			m_Keyboard.update();
			m_Mouse.update();
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "GL ERROR: " << error << std::endl;
				getFirstNMessages(1);
			}
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void Window::getFirstNMessages(GLuint numMsgs)
		{
			GLint maxMsgLen = 0;
			glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);

			std::vector<GLchar> msgData(numMsgs * maxMsgLen);
			std::vector<GLenum> sources(numMsgs);
			std::vector<GLenum> types(numMsgs);
			std::vector<GLenum> severities(numMsgs);
			std::vector<GLuint> ids(numMsgs);
			std::vector<GLsizei> lengths(numMsgs);

			GLuint numFound = glGetDebugMessageLog(numMsgs, msgData.size(), &sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);

			sources.resize(numFound);
			types.resize(numFound);
			severities.resize(numFound);
			ids.resize(numFound);
			lengths.resize(numFound);

			std::vector<std::string> messages;
			messages.reserve(numFound);

			std::vector<GLchar>::iterator currPos = msgData.begin();
			for (size_t msg = 0; msg < lengths.size(); ++msg)
			{
				messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
				currPos = currPos + lengths[msg];
			}
			for (size_t i = 0; i < messages.size(); i++) {
				std::cout << messages.at(i).c_str() << std::endl;
			}
		}

		void onKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keyboard.setKeyState(key, action != GLFW_RELEASE);
		}

		void onMouseMove(GLFWwindow* window, double mx, double my) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Mouse.setX(mx);
			win->m_Mouse.setY(my);
		}

		void Window::getMousePosition(double& x, double& y) {
			x = m_Mouse.getX();
			y = m_Mouse.getY();
		}

		void onMouseChange(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Mouse.setButtonState(button, action != GLFW_RELEASE);
		}

		void onWindowResize(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}
	}
}