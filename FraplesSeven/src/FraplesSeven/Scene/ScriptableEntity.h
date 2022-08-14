#pragma once
#include "Entity.h"

namespace Fraples
{
	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return _mEntity.GetComponent<T>();
		}
		virtual ~ScriptableEntity() = default;
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeSteps ) {}
	private:
		Entity _mEntity;
		friend class Scene;
	};
}