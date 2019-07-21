#pragma once

#ifndef EVENT_H
#define EVENT_H

#include "Event.h"
#endif

namespace Eu
{

	class  KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected: 
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

			int m_KeyCode;
	};

	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatcount)
			: KeyEvent(keycode), m_RepeatCount(repeatcount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " Repeats: " << m_RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}



		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};


	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}



		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};


}