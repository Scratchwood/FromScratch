#ifndef FROMSCRATCH_INCLUDE_MOUSE
#define FROMSCRATCH_INCLUDE_MOUSE
#define MAX_BUTTONS 32

namespace fs {
	namespace input {
		class Mouse {
		private:
			bool   m_CurrentState[MAX_BUTTONS];
			bool   m_LastState[MAX_BUTTONS];
			double m_Cx, m_Cy;
		public:
			Mouse();

			inline double getX() const { return m_Cx; }
			inline double getY() const { return m_Cy; }

			inline void setX(double x) { m_Cx = x; }
			inline void setY(double y) { m_Cy = y; }

			void update();

			inline void setButtonState(unsigned int button, bool state)
			{
				m_CurrentState[button] = state;
			}

			inline bool isPressed(unsigned int button) const
			{
				return m_CurrentState[button];
			}

			inline bool wasClicked(unsigned int button) const
			{
				return m_CurrentState[button] && !m_LastState[button];
			}
		};
	}
}
#endif