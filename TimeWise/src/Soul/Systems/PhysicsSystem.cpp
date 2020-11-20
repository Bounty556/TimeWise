#include "PhysicsSystem.h"

#include <Structures/CommandQueue.h>
#include <Utility/Math.h>

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
			
			UniquePointer<sf::Vector2f> verticesA(m_Colliders[i].Element.GetVertices());
			unsigned int vertexCountA = m_Colliders[i].Element.GetVertexCount();

			for (unsigned int j = i + 1; j < m_Colliders.Count(); ++j)
			{
				UniquePointer<sf::Vector2f> verticesB(m_Colliders[j].Element.GetVertices());
				unsigned int vertexCountB = m_Colliders[j].Element.GetVertexCount();

				bool firstPolygon;
				sf::Vector2f* collidedPoint = MyCollision(verticesA.Raw(), vertexCountA, m_Colliders[i].Element.GetCenter(), verticesB.Raw(), vertexCountB, m_Colliders[j].Element.GetCenter(), firstPolygon);

				if (collidedPoint)
				{
					sf::Vector2f correction;
					if (firstPolygon)
					{
						// Find closest edge to point
						correction = Math::CorrectionVector(*collidedPoint, verticesB.Raw(), vertexCountB);
						m_Colliders[i].Element.HandleCollision(*collidedPoint, correction, m_Colliders[j].Element);
						m_Colliders[j].Element.HandleCollision(*collidedPoint, -correction, m_Colliders[i].Element);
					}
					else
					{
						correction = Math::CorrectionVector(*collidedPoint, verticesA.Raw(), vertexCountA);
						m_Colliders[i].Element.HandleCollision(*collidedPoint, -correction, m_Colliders[j].Element);
						m_Colliders[j].Element.HandleCollision(*collidedPoint, correction, m_Colliders[i].Element);
					}
				}
			}

			m_Colliders[i].Element.DrawCollider(context);
		}
	}

	sf::Vector2f* PhysicsSystem::MyCollision(sf::Vector2f* polygonA, unsigned int vertexCountA, const sf::Vector2f& centerA, sf::Vector2f* polygonB, unsigned int vertexCountB, const sf::Vector2f& centerB, bool& firstPolygon)
	{
		for (unsigned int i = 0; i < vertexCountA; ++i)
		{
			if (Math::IsPointInPolygon(polygonA[i], polygonB, vertexCountB, centerB))
			{
				firstPolygon = true;
				return &polygonA[i];
			}
		}

		for (unsigned int i = 0; i < vertexCountB; ++i)
		{
			if (Math::IsPointInPolygon(polygonB[i], polygonA, vertexCountA, centerA))
			{
				firstPolygon = false;
				return &polygonB[i];
			}
		}

		return nullptr;
	}

	bool PhysicsSystem::SATCollision(unsigned int normalCount, unsigned int vertexCountA, unsigned int vertexCountB, const UniquePointer<sf::Vector2f>& normals, const UniquePointer<sf::Vector2f>& verticesA, const UniquePointer<sf::Vector2f>& verticesB)
	{
		for (unsigned int k = 0; k < normalCount; ++k)
		{
			float minA = 999999999.0f;
			float maxA = -999999999.0f;
			float minB = 999999999.0f;
			float maxB = -999999999.0f;

			for (unsigned int l = 0; l < vertexCountA; ++l)
			{
				float value = Math::Dot(verticesA[l], normals[k]);
				minA = Math::Min(minA, value);
				maxA = Math::Max(maxA, value);
			}

			for (unsigned int l = 0; l < vertexCountB; ++l)
			{
				float value = Math::Dot(verticesB[l], normals[k]);
				minB = Math::Min(minB, value);
				maxB = Math::Max(maxB, value);
			}

			if (!(maxA > minB && maxA < maxB) && !(minA > minB && minA < maxB))
			{
				return false;
			}
		}

		return true;
	}
}