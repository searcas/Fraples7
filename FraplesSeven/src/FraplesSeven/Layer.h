#pragma once

#include "FraplesSeven/Core.h"
#include "FraplesSeven/Events/Events.h"



namespace Fraples
{

	class FPL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate()	{ }
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName()const { return _mDebugName; }

	protected:
		std::string _mDebugName;
	};

}