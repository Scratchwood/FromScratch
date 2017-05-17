#ifndef FROMSCRATCH_INCLUDE_KEYBOARD
#define FROMSCRATCH_INCLUDE_KEYBOARD
#define MAX_KEYS 1024

namespace fs {
	namespace input {
		class Keyboard {
		private:
			bool m_CurrentState[MAX_KEYS];
			bool m_LastState[MAX_KEYS];
		public:
			Keyboard();

			void update();

			inline void setKeyState(unsigned int key, bool state)
			{
				m_CurrentState[key] = state;
			}

			inline bool isKeyDown(unsigned int key) const
			{
				return m_CurrentState[key];
			}

			inline bool wasKeyPressed(unsigned int key) const
			{
				return m_CurrentState[key] && !m_LastState[key];
			}
		};
	}
}
#endif