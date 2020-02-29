#pragma once
#include "Precompile.h"
#include "Core/Core.h" //宏定义头文件

//#include <string>
//#include <functional>//STL 定义运算函数（代替运算符） 定义运算符

//移动到precompile.h里


namespace Molers
{
		//https://blog.csdn.net/thinkerleo1997/article/details/80355905
		//C++11的enum class 、enum struct 和 enum
		//c++11 强类型枚举 enum class https://www.cnblogs.com/moodlxs/p/10174533.html

	//enum（非enum class\enum struct）会发生自动数据类型转换。但是enum class\enum struct是不允许这么做的。
	enum class EventType//事件类型
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	//c++中bit是位域 c语言中 bit和int char之类的差不多，只不过char=8位, bit=1位而已。
	//都是变量，编译器在编译过程中分配地。。bit只有0和1两种值..

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),//1 bit左移 1左移0位 1
		EventCategoryInput = BIT(1),//2 1左移1位 10
		EventCategoryKeyboard = BIT(2), //4   100
		EventCategoryMouse = BIT(3), //8 1000
		EventCategoryMouseButton = BIT(4) //16   10000
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }	

	class __declspec(dllexport) Event
	{
		friend class EventDispatcher;
	public:
		bool Handled = false;//处理

		//纯虚函数必须被子类实现 不能被实例化 

		virtual EventType GetEventType() const = 0; 
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
	//事件调度员 监听事件
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) //构造函数
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler 泛型编程
		//C++ 模板  https://www.runoob.com/cplusplus/cpp-templates.html

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{ 
				m_Event.Handled = func(static_cast<T&>(m_Event)); //static_cast是一个c++运算符，功能是把一个表达式转换为某种类型 强制类型转换
				// Event 强制类型转换为T类型 T类型可能是int string double EventType
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}


//C++ 模板
//https://www.runoob.com/cplusplus/cpp-templates.html

//static_cast
//https://baike.baidu.com/item/static_cast/4472966
//static_cast、dynamic_cast、const_cast、reinterpret_cast
//https://www.cnblogs.com/chenyangchun/p/6795923.html


//Event Dispatcher 分发器 事件调度器
//WTF Is? Event Dispatchers in Unreal Engine 4
//https://www.youtube.com/watch?v=ayCEqL7XFZY  
//HTF do I ? Event Dispatchers in Unreal Engine 4
//https://www.youtube.com/watch?v=sEcoWGrF1Hg

//如果触发了某个事件，调用 EventDispatcher 的方法告诉分发器，
//分发器根据 Director类传过来的类型，
//去对应侦听器里查找，根据事件的具体行为，触发侦听器对应的回调方法，
//自己注册的方法就能接受到响应。

//事件调度器的原理与接口相似，但也有自己独特的优势。接口的调用，只能调用一个实现，
//而事件调度器的调用，可以是一个事件被驱动，也可能是N个事件被驱动

//When an event is dispatched via the dispatcher,
//it notifies all listeners registered with that event:
//当一个事件通过dispatcher发送时，它会通知所有注册了该事件的监听器:

