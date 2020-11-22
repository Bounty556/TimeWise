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
			m_Colliders[i].Element.Update(dt);

			for (unsigned int j = i + 1; j < m_Colliders.Count(); ++j)
			{
				sf::Vector2f correction = CheckColliding(m_Colliders[i].Element, m_Colliders[j].Element);

				if (Math::Magnitude(correction) > 0)
				{
					SoulLogInfo("Colliding!");
				}
			}

			m_Colliders[i].Element.DrawCollider(context);
		}
	}

	sf::Vector2f PhysicsSystem::CheckColliding(const Collider& a, const Collider& b)
	{
		sf::Vector2f direction(1.0f, 0.0f);
	}

	sf::Vector2f PhysicsSystem::Support(const Collider& a, const Collider& b, sf::Vector2f& direction)
	{
		return a.FarthestVertex(direction) - b.FarthestVertex(-direction);
	}
}