#include "FplPCH.h"
#include "LayerStack.h"


namespace Fraples
{
	LayerStack::LayerStack()
	{
		
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : _mLayers)
			delete layer;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		_mLayers.emplace(_mLayers.begin() + _mLayerInsertIndex, layer);
		layer->OnAttach();
		_mLayerInsertIndex++;
	}
	void LayerStack::PushOverLay(Layer* overlay)
	{
		_mLayers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Layer* poplayer)
	{
		auto it = std::find(_mLayers.begin(), _mLayers.end(), poplayer);

		if (it !=_mLayers.end())
		{
			_mLayers.erase(it);
			_mLayerInsertIndex--;
			poplayer->OnDetach();
		}

	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(_mLayers.begin(), _mLayers.end(), overlay);
		if (it != _mLayers.end())
		{
			_mLayers.erase(it);
			overlay->OnDetach();
		}
	}
}