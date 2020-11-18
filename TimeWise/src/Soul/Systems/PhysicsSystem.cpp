#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>

namespace Soul
{
	PhysicsSystem::PhysicsSystem(unsigned int capacity) :
		m_Colliders(capacity)
	{

	}

	void PhysicsSystem::Update(float dt, Context& context)
	{
		while (context.CommandQueue.CheckMessage("Remove Collider"))
		{
			CommandQueue::Message& message = context.CommandQueue.ConsumeMessage();
			m_Colliders.FreeObject((Collider*)message.Data);
		}

		for (unsigned int i = 0; i < m_Colliders.Count(); ++i)
		{
			m_Colliders[i].Element.DrawCollider(context);
		}

		// TODO: Broad phase collision checking
		// TODO: Narrow phase collision checking
	}
}