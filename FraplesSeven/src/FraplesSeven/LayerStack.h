#pragma once
#include "Layer.h"	








namespace Fraples
{
	class FPL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* push);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _mLayers.begin(); }
		std::vector<Layer*>::iterator end() { return _mLayers.end(); }

	private:
		std::vector<Layer*> _mLayers;
		std::vector<Layer*>::iterator _mLayerInsert;
	};
}