#include "Collider.h"

#include <cstdarg>

#include <Other/DebugDrawer.h>

namespace Soul
{
	Collider::Collider(Entity* entity, unsigned int vertexCount, ...) :
		Component(entity),
		m_VertexCount(vertexCount),
		m_Vertices(PartitionArray(sf::Vector2f, m_VertexCount)),
		m_IsSolid(false),
		m_Bounciness(0.0f),
		m_Friction(0.5f)
	{
		va_list args;
		va_start(args, vertexCount);

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			m_Vertices[i] = va_arg(args, sf::Vector2f);
		}
	}

	const sf::Vector2f& Collider::operator[](unsigned int index) const
	{
		return m_Vertices[index];
	}

	const char* Collider::GetType() const
	{
		return "Collider";
	}

	void Collider::DrawCollider(Context& context) const
	{
		for (unsigned int i = 0; i < m_VertexCount; i++)
		{
			if (i == m_VertexCount - 1)
			{
				context.DebugDrawer.AddLine(m_Vertices[i], m_Vertices[0]);
			}
			else
			{
				context.DebugDrawer.AddLine(m_Vertices[i], m_Vertices[i + 1]);
			}
		}
	}

	unsigned int Collider::GetVertexCount() const
	{
		return m_VertexCount;
	}
	
	bool Collider::IsSolid() const
	{
		return m_IsSolid;
	}

	float Collider::GetBounciness() const
	{
		return m_Bounciness;
	}

	float Collider::GetFriction() const
	{
		return m_Friction;
	}

	void Collider::SetIsSolid(bool isSolid)
	{
		m_IsSolid = isSolid;
	}

	void Collider::SetBounciness(float bounciness)
	{
		m_Bounciness = bounciness;
	}

	void Collider::SetFriction(float friction)
	{
		m_Friction = friction;
	}
}