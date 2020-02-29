#include "Precompile.h"
#include "LayerStack.h"

namespace Molers {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}
	//增加图层
	void LayerStack::PushLayer(Layer* layer)
	{
	
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}
	//入栈
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}
	//出栈 弹出图层
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			//layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}
	//弹出叠加层
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			//overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}