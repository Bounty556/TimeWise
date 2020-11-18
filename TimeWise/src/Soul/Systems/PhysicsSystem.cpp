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
			m_Colliders[i].Element.DrawCollider(context);
			
			UniquePointer<sf::Vector2f> axesA(m_Colliders[i].Element.GetOffsetNormals());
			UniquePointer<sf::Vector2f> verticesA(m_Colliders[i].Element.GetOffsetVertices());
			unsigned int aVertices = m_Colliders[i].Element.GetVertexCount();

			for (unsigned int j = i + 1; j < m_Colliders.Count(); ++j)
			{
				UniquePointer<sf::Vector2f> axesB(m_Colliders[j].Element.GetOffsetNormals());
				UniquePointer<sf::Vector2f> verticesB(m_Colliders[j].Element.GetOffsetVertices());
				unsigned int bVertices = m_Colliders[j].Element.GetVertexCount();
				bool skipCheck = false;

				// Narrow phase collision
				if (SATCollision(aVertices, aVertices, bVertices, axesA, verticesA, verticesB) && SATCollision(bVertices, aVertices, bVertices, axesB, verticesA, verticesB))
				{
					SoulLogInfo("Collision detected!");
				}
			}
		}
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