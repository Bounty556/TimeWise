#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>
#include <Structures/Set.h>
#include <Utility/ConvexHull.h>
#include <Utility/Math.h>
#include <Utility/Simplex.h>
#include <Entities/Entity.h>

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
			Collider& a = m_Colliders[i].Element;
			a.Update(dt);

			for (unsigned int j = i + 1; j < m_Colliders.Count(); ++j)
			{
				Collider& b = m_Colliders[j].Element;

				if (Math::Magnitude(a.GetCenter() - b.GetCenter()) <= a.GetRadius() + b.GetRadius())
				{
					sf::Vector2f correction;
					if (CheckColliding(a, b, correction))
					{
						a.HandleCollision(dt, sf::Vector2f(0.0f, 0.0f), correction, b);
						b.HandleCollision(dt, sf::Vector2f(0.0f, 0.0f), -correction, a);
					}
				}
			}

			a.DrawCollider(context);
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

		//while (true)
		for (unsigned int i = 0; i < 25; ++i)
		{
			support = Support(a, b, direction);
			if (Math::Dot(support, direction) < 0)
			{
				return false;
			}
			simplex.AddVertex(support);
			if (simplex.DoGJK(direction))
			{
				Set<sf::Vector2f> minkowski(a.GetVertexCount() * b.GetVertexCount());
				UniquePointer<sf::Vector2f> verticesA(std::move(a.GetVertices()));
				UniquePointer<sf::Vector2f> verticesB(std::move(b.GetVertices()));
				for (unsigned int i = 0; i < a.GetVertexCount(); ++i)
				{
					for (unsigned int j = 0; j < b.GetVertexCount(); ++j)
					{
						minkowski.Add(verticesA[i] - verticesB[j]);
					}
				}

				ConvexHull minkowskiHull(minkowski);

				float smallestDistance = 99999999.0f;
				sf::Vector2f smallestReject;

				// Find the nearest point on the edge of the minkowski difference
				for (unsigned int i = 0; i < minkowskiHull.Length(); ++i)
				{
					sf::Vector2f edge = minkowskiHull[(i + 1) % minkowskiHull.Length()]- minkowskiHull[i];
					sf::Vector2f reject = Math::Reject(-minkowskiHull[i], edge);
					float distance = Math::Magnitude(reject);

					if (distance < smallestDistance)
					{
						smallestDistance = distance;
						smallestReject = reject;
					}
				}

				correction = smallestReject;

				return true;
			}
		}

		return false;
	}

	sf::Vector2f PhysicsSystem::Support(const Collider& a, const Collider& b, sf::Vector2f& direction)
	{
		return a.FarthestVertex(direction) - b.FarthestVertex(-direction);
	}
}