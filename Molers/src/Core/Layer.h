#pragma once

#include "Core/Core.h"
#include "Events/Events.h"

namespace Molers {

	class __declspec(dllexport) Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() ;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		//Í¼²ãµÄÃû×Ö
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

