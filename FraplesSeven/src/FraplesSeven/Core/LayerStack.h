#pragma once
#include "Layer.h"	








namespace Fraples
{
	class  LayerStack
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
		std::vector<Layer*>::reverse_iterator rbegin() { return _mLayers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return _mLayers.rend(); }


		std::vector<Layer*>::const_iterator begin() const { return _mLayers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return _mLayers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin()const { return _mLayers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return _mLayers.rend(); }
		
	private:
		std::vector<Layer*> _mLayers;
		unsigned int _mLayerInsertIndex = 0;
	};
}