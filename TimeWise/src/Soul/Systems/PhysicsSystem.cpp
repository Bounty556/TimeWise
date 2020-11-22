#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>
#include <Utility/Math.h>
#include <Utility/Simplex.h>

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

		// TODO: Better broad phase collision checking?
		for (unsigned int i = 0; i < m_Colliders.Count(); ++i)
		{

		}
	}
}