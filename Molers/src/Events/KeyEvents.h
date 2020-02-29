#pragma once
#include "Events/Events.h"

//#include <sstream>

namespace Molers
{
	//按的哪个键
	class __declspec(dllexport) KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; } 

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)//事件的类别
			//virtual int GetCategoryFlags() const override { return category; }	

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};
	//返回按键重复的次数
	class __declspec(dllexport) KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		//static EventType GetStaticType() { return EventType::KeyPressed; }\
		//	virtual EventType GetEventType() const override { return GetStaticType(); }\
			//virtual const char* GetName() const override { return "KeyPressed"; }
		//↑👆
		//相同
		//↓👇

		EVENT_CLASS_TYPE(KeyPressed)//键盘事件的详细
	private:
		int m_RepeatCount;//重复次数
	};
	//释放的按键
	class __declspec(dllexport) KeyReleasedEvent : public KeyEvent
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

	class __declspec(dllexport) KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};


}