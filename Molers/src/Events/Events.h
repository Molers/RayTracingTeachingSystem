#pragma once
#include "Precompile.h"
#include "Core/Core.h" //�궨��ͷ�ļ�

//#include <string>
//#include <functional>//STL �������㺯��������������� ���������

//�ƶ���precompile.h��


namespace Molers
{
		//https://blog.csdn.net/thinkerleo1997/article/details/80355905
		//C++11��enum class ��enum struct �� enum
		//c++11 ǿ����ö�� enum class https://www.cnblogs.com/moodlxs/p/10174533.html

	//enum����enum class\enum struct���ᷢ���Զ���������ת��������enum class\enum struct�ǲ�������ô���ġ�
	enum class EventType//�¼�����
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	//c++��bit��λ�� c������ bit��int char֮��Ĳ�ֻ࣬����char=8λ, bit=1λ���ѡ�
	//���Ǳ������������ڱ�������з���ء���bitֻ��0��1����ֵ..

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),//1 bit���� 1����0λ 1
		EventCategoryInput = BIT(1),//2 1����1λ 10
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
		bool Handled = false;//����

		//���麯�����뱻����ʵ�� ���ܱ�ʵ���� 

		virtual EventType GetEventType() const = 0; 
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
	//�¼�����Ա �����¼�
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) //���캯��
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler ���ͱ��
		//C++ ģ��  https://www.runoob.com/cplusplus/cpp-templates.html

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{ 
				m_Event.Handled = func(static_cast<T&>(m_Event)); //static_cast��һ��c++������������ǰ�һ�����ʽת��Ϊĳ������ ǿ������ת��
				// Event ǿ������ת��ΪT���� T���Ϳ�����int string double EventType
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


//C++ ģ��
//https://www.runoob.com/cplusplus/cpp-templates.html

//static_cast
//https://baike.baidu.com/item/static_cast/4472966
//static_cast��dynamic_cast��const_cast��reinterpret_cast
//https://www.cnblogs.com/chenyangchun/p/6795923.html


//Event Dispatcher �ַ��� �¼�������
//WTF Is? Event Dispatchers in Unreal Engine 4
//https://www.youtube.com/watch?v=ayCEqL7XFZY  
//HTF do I ? Event Dispatchers in Unreal Engine 4
//https://www.youtube.com/watch?v=sEcoWGrF1Hg

//���������ĳ���¼������� EventDispatcher �ķ������߷ַ�����
//�ַ������� Director�ഫ���������ͣ�
//ȥ��Ӧ����������ң������¼��ľ�����Ϊ��������������Ӧ�Ļص�������
//�Լ�ע��ķ������ܽ��ܵ���Ӧ��

//�¼���������ԭ����ӿ����ƣ���Ҳ���Լ����ص����ơ��ӿڵĵ��ã�ֻ�ܵ���һ��ʵ�֣�
//���¼��������ĵ��ã�������һ���¼���������Ҳ������N���¼�������

//When an event is dispatched via the dispatcher,
//it notifies all listeners registered with that event:
//��һ���¼�ͨ��dispatcher����ʱ������֪ͨ����ע���˸��¼��ļ�����:

