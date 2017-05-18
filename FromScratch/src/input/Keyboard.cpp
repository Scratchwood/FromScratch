#include "keyboard.h"
#include <cstring>

namespace fs {
	namespace input {
		Keyboard::Keyboard() {
			for (int i = 0; i < MAX_KEYS; ++i)
			{
				m_CurrentState[i] = false;
				m_LastState[i] = false;
			}
		}

		void Keyboard::update() {
			memcpy(m_LastState, m_CurrentState, MAX_KEYS);
		}
	}
}