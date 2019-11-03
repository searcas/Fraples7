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
		{
			layer->OnDetach();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		_mLayers.emplace(_mLayers.begin() + _mLayerInsertIndex, layer);
		_mLayerInsertIndex++;
		layer->OnAttach();
	}
	void LayerStack::PushOverLay(Layer* overlay)
	{
		_mLayers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Layer* poplayer)
	{
		auto it = std::find(_mLayers.begin(), _mLayers.begin() + _mLayerInsertIndex, poplayer);

		if (it != _mLayers.end() + _mLayerInsertIndex)
		{
			poplayer->OnDetach();
			_mLayers.erase(it);
			_mLayerInsertIndex--;
		}

	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(_mLayers.begin() + _mLayerInsertIndex, _mLayers.end(), overlay);
		if (it != _mLayers.end())
		{
			overlay->OnDetach();
			_mLayers.erase(it);
		}
	}
}