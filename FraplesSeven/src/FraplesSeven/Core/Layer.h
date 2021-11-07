#pragma once

#include "FraplesSeven/Core/Core.h"
#include "FraplesSeven/Events/Events.h"

#include "FraplesSeven/Core/TimeSteps.h" 

namespace Fraples
{

	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate(TimeSteps timesteps)	{ }
		virtual void OnImGuiRender(){ }
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName()const { return _mDebugName; }

	protected:
		std::string _mDebugName;
	};

}