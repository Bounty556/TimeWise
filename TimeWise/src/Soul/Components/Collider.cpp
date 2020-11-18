#include "Collider.h"

#include <cstdarg>

#include <Components/Rigidbody.h>
#include <Entities/Entity.h>
#include <Other/DebugDrawer.h>
#include <Structures/CommandQueue.h>
#include <Utility/Math.h>

namespace Soul
{
	Collider::Collider(Entity* entity, unsigned int vertexCount, ...) :
		Component(entity),
		m_VertexCount(vertexCount),
		m_Vertices(PartitionArray(sf::Vector2f, m_VertexCount)),
		m_Normals(PartitionArray(sf::Vector2f, m_VertexCount)),
		m_Handler(nullptr)
	{
		va_list args;
		va_start(args, vertexCount);

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			m_Vertices[i] = va_arg(args, sf::Vector2f);
		}

		for (unsigned int i = 0; i < m_VertexCount; i++)
		{
			if (i == m_VertexCount - 1)
			{
				m_Normals[i] = Math::CalculateNormal(m_Vertices[i], m_Vertices[0]);
			}
			else
			{
				m_Normals[i] = Math::CalculateNormal(m_Vertices[i], m_Vertices[i + 1]);
			}
		}
	}

	void Collider::DrawCollider(Context& context) const
	{
		sf::Vector2f offset(0.0f, 0.0f);

		if (m_AffectedEntity)
		{
			offset = m_AffectedEntity->getPosition();
		}

		for (unsigned int i = 0; i < m_VertexCount; i++)
		{
			if (i == m_VertexCount - 1)
			{
				context.DebugDrawer.AddLine(m_Vertices[i] + offset, m_Vertices[0] + offset);
			}
			else
			{
				context.DebugDrawer.AddLine(m_Vertices[i] + offset, m_Vertices[i + 1] + offset);
			}
		}
	}

	bool Collider::CleanUp(Context& context)
	{
		context.CommandQueue.QueueMessage("Remove Collider", this);
		return false;
	}

	void Collider::HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		if (m_Handler)
		{
			m_Handler->HandleCollision(contactPoint, correction, collider);
		}
	}

	void Collider::Update(float dt)
	{
		if (m_Handler)
		{
			m_Handler->Update(dt);
		}
	}

	void Collider::SetHandler(CollisionHandler* handler)
	{
		m_Handler = handler;
	}

	const UniquePointer<sf::Vector2f>& Collider::GetVertices() const
	{
		return m_Vertices;
	}

	const UniquePointer<sf::Vector2f>& Collider::GetNormals() const
	{
		return m_Normals;
	}

	UniquePointer<sf::Vector2f> Collider::GetOffsetVertices() const
	{
		UniquePointer<sf::Vector2f> vertices(PartitionArray(sf::Vector2f, m_VertexCount));

		// TODO: Include rotation

		sf::Vector2f offset(0.0f, 0.0f);

		if (m_AffectedEntity)
		{
			offset = m_AffectedEntity->getPosition();
		}

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			vertices[i] = m_Vertices[i] + offset;
		}

		return std::move(vertices);
	}

	UniquePointer<sf::Vector2f> Collider::GetOffsetNormals() const
	{
		UniquePointer<sf::Vector2f> normals(PartitionArray(sf::Vector2f, m_VertexCount));

		// TODO: Include rotation

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			normals[i] = m_Normals[i];
		}

		return std::move(normals);
	}

	const char* Collider::GetType() const
	{
		return "Collider";
	}

	unsigned int Collider::GetVertexCount() const
	{
		return m_VertexCount;
	}
}