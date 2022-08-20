#pragma once
#include "Scene.h"
#include "FraplesSeven/Core/Core.h"

namespace Fraples
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity&) = default;
		template<typename T>
		bool HasComponent()
		{
			return _mScene->_mRegistry.all_of<T>(_mEntityHandle);
		}
		template<typename T, typename ... Args>
		T& AddComponent(Args&&...  args)
		{
			FPL_ASSERT("Component already exist.", !HasComponent<T>());
			T& component = _mScene->_mRegistry.emplace<T>(_mEntityHandle, std::forward<Args>(args)...);
			_mScene->OnComponentAdded<T>(*this, component);
			return component;
		}
		template<typename T>
		T& GetComponent()
		{
			FPL_ASSERT("Has no component.", HasComponent<T>());
			return _mScene->_mRegistry.get<T>(_mEntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			FPL_ASSERT("Has no component.", HasComponent<T>());
			_mScene->_mRegistry.remove<T>(_mEntityHandle);
		}
		
		operator entt::entity () const { return _mEntityHandle; }
		operator bool() const { return _mEntityHandle != entt::null; }
		operator uint32_t()const { return (uint32_t)_mEntityHandle; }
		bool operator ==(const Entity& rhs)const { return _mEntityHandle == rhs._mEntityHandle && _mScene == rhs._mScene; }
		bool operator !=(const Entity& rhs)const { return !operator==(rhs); }
	private:
		entt::entity _mEntityHandle = entt::null;
		Scene* _mScene = nullptr;
	};
}
