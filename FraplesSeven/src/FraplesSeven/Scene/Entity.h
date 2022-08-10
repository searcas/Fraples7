#pragma once
#include "Scene.h"


namespace Fraples
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity&) = default;

		template<typename T, typename ... Args>
		T& AddComponent(Args&&...  args)
		{
			return _mScene->_mRegistry.emplace<T>(_mEntityHandle, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent()
		{
			return _mScene->_mRegistry.get<T>(_mEntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			_mScene->_mRegistry.remove<T>(_mEntityHandle);
		}
		operator bool() const { return _mEntityHandle != entt::null; }

	private:
		entt::entity _mEntityHandle = entt::null;
		Scene* _mScene = nullptr;
	};
}
