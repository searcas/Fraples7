#include "FplPCH.h"
#include "LayerStack.h"


namespace Fraples
{
	LayerStack::LayerStack()
	{
		_mLayerInsert = _mLayers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : _mLayers)
			delete layer;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		_mLayerInsert = _mLayers.emplace(_mLayerInsert, layer);
	}
	void LayerStack::PushOverLay(Layer* overlay)
	{
		_mLayers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* poplayer)
	{
		auto it = std::find(_mLayers.begin(), _mLayers.end(), poplayer);

		if (it !=_mLayers.end())
		{
			_mLayers.erase(it);
			_mLayerInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(_mLayers.begin(), _mLayers.end(), overlay);
		if (it != _mLayers.end())
			_mLayers.erase(it);
	}
}