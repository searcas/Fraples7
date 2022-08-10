#pragma once
#include "entt.hpp"
#include "../Core/TimeSteps.h"
namespace Fraples
{

	class Scene
	{
		friend class Entity;
	public:
		Scene() = default;
		~Scene();
		Entity CreateEntity(const std::string& tag ="");
		void OnUpdate(TimeSteps ts);
		
	private:
		entt::registry _mRegistry;  
	};
}