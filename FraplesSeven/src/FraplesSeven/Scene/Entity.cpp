#include "FplPCH.h"
#include "Entity.h"

namespace Fraples
{
	Entity::Entity(entt::entity handle, Scene* scene) :_mEntityHandle(handle), _mScene(scene)
	{
	}
}