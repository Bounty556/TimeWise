#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>
#include <Structures/Set.h>
#include <Utility/ConvexHull.h>
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
				sf::Vector2f correction;
				if (CheckColliding(m_Colliders[i].Element, m_Colliders[j].Element, correction))
				{
					SoulLogInfo("Colliding");
				}
			}

			m_Colliders[i].Element.DrawCollider(context);
		}
	}

	bool PhysicsSystem::CheckColliding(const Collider& a, const Collider& b, sf::Vector2f& correction)
	{
		sf::Vector2f direction(1.0f, 0.0f);
		Simplex simplex;
		unsigned int maxAttempts = 50;

		sf::Vector2f support(Support(a, b, direction));
		simplex.AddVertex(support);
		direction = Math::Normalize(-support);

		//for (unsigned int i = 0; i < maxAttempts; ++i)
		while (true)
		{
			support = Support(a, b, direction);
			if (Math::Dot(support, direction) < 0)
			{
				return false;
			}
			simplex.AddVertex(support);
			if (simplex.DoGJK(direction))
			{
				float edgeDistance;
				sf::Vector2f edgeNormal;
				unsigned int edgeIndex;
				while (false)
				{
					simplex.FindClosestEdge(edgeNormal, edgeDistance, edgeIndex, sf::Vector2f(0.0f, 0.0f));

					support = Support(a, b, edgeNormal); // Search in the direction of the edge normal

					// Check to see if this support is on the closest edge.
					float supportDistance = Math::Dot(support, edgeNormal);
					if (supportDistance - edgeDistance < .00001f)
					{
						// If this is the case, then we have found our solution.
						correction = edgeDistance * edgeNormal;
						return true;
					}
					else
					{
						// Add this point to our simplex and continue the search.
						simplex.InsertVertex(edgeIndex, support);
					}
				}
			}
		}

		return false;
	}

	sf::Vector2f PhysicsSystem::Support(const Collider& a, const Collider& b, sf::Vector2f& direction)
	{
		return a.FarthestVertex(direction) - b.FarthestVertex(-direction);
	}
}