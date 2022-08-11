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
		void OnViewPortResize(uint32_t width, uint32_t height);
	private:
		entt::registry _mRegistry;  
		uint32_t _mViewPortWidth{0};
		uint32_t _mViewPortHeight{0};
	};
}