#ifndef FROMSCRATCH_INCLUDE_WINDOW
#define FROMSCRATCH_INCLUDE_WINDOW
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "keyboard.h"
#include "mouse.h"


namespace fs {
	namespace window {
		class Window {
		private:
			int m_Width, m_Height;
			const char* m_Name;
			GLFWwindow* m_Window;
			bool m_Closed;
			input::Keyboard m_Keyboard;
			input::Mouse m_Mouse;

		public:
			Window(const char* name, int width, int height);
			~Window();

			bool closed() const;
			void clear() const;
			void update();

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }
			inline bool wasKeyPressed(const int& keycode) const { return m_Keyboard.wasKeyPressed(keycode); };
			inline bool isKeyDown(const int& keycode) const { return m_Keyboard.isKeyDown(keycode); };
			inline bool wasMouseClicked(const int& button) const { return m_Mouse.wasClicked(button); };
			void getMousePosition(double& x, double&y);

		private:
			void getFirstNMessages(GLuint nuimMsgs);
			bool init();
			friend static void onWindowResize(GLFWwindow* window, int width, int height);
			friend static void onKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void onMouseMove(GLFWwindow* window, double mx, double my);
			friend static void onMouseChange(GLFWwindow* window, int button, int action, int mods);
		};
	}
}
#endif
