#include "PhysicsSystem.h"

namespace Soul
{
	PhysicsSystem::PhysicsSystem(unsigned int maxColliders) :
		m_Components(maxColliders)
	{

	}

	PhysicsSystem::~PhysicsSystem()
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			MemoryManager::FreeMemory(m_Components[i]);
		}
	}

	void PhysicsSystem::Update(float dt, Context& context)
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->HandleCollision(dt, context);
		}
		// TODO: Oriented AABB collision checks
	}
}