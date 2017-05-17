#include "mouse.h"
#include <cstring>

namespace fs {
	namespace input {
		Mouse::Mouse()
		{
			for (int i = 0; i < MAX_BUTTONS; ++i) {
				m_CurrentState[i] = false;
				m_LastState[i] = false;
			}
		}

		void Mouse::update() {
			memcpy(m_LastState, m_CurrentState, MAX_BUTTONS);
		}
	}
}