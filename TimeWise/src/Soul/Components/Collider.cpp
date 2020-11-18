#include "Collider.h"

#include <cstdarg>

#include <Entities/Entity.h>
#include <Other/DebugDrawer.h>
#include <Structures/CommandQueue.h>

namespace Soul
{
	Collider::Collider(Entity* entity, unsigned int vertexCount, ...) :
		Component(entity),
		m_VertexCount(vertexCount),
		m_Vertices(PartitionArray(sf::Vector2f, m_VertexCount))
	{
		va_list args;
		va_start(args, vertexCount);

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			m_Vertices[i] = va_arg(args, sf::Vector2f);
		}
	}

	const sf::Vector2f Collider::operator[](unsigned int index) const
	{
		sf::Vector2f offset(0.0f, 0.0f);

		if (m_AffectedEntity)
		{
			offset = m_AffectedEntity->getPosition();
		}

		return m_Vertices[index] + offset;
	}

	const char* Collider::GetType() const
	{
		return "Collider";
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

	unsigned int Collider::GetVertexCount() const
	{
		return m_VertexCount;
	}

	bool Collider::CleanUp(Context& context)
	{
		context.CommandQueue.QueueMessage("Remove Collider", this);
		return false;
	}
}