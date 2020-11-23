#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>
#include <Structures/Set.h>
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
		direction = -support;

		for (unsigned int i = 0; i < maxAttempts; ++i)
		{
			support = Support(a, b, direction);
			if (Math::Dot(support, direction) < 0)
			{
				return false;
			}
			simplex.AddVertex(support);
			if (simplex.DoSimplex(direction))
			{
				// Calculate Minkowski difference
				Set<sf::Vector2f> minkowski(a.GetVertexCount() * b.GetVertexCount());
				UniquePointer<sf::Vector2f> aVertices(std::move(a.GetVertices()));
				UniquePointer<sf::Vector2f> bVertices(std::move(b.GetVertices()));

				for (unsigned int j = 0; j < a.GetVertexCount(); ++j)
				{
					minkowski.Add(aVertices[j]);
				}

				for (unsigned int j = 0; j < b.GetVertexCount(); ++j)
				{
					minkowski.Add(bVertices[j]);
				}

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