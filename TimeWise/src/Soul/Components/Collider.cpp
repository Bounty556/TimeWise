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
		Component(entity, "Collider"),
		m_VertexCount(vertexCount),
		m_Vertices(PartitionArray(sf::Vector2f, m_VertexCount)),
		m_Center(0.0f, 0.0f),
		m_Handler(nullptr),
		m_Radius(0.0f),
		m_Mass(1.0f),
		m_Bounciness(0.0f),
		m_Friction(0.5f),
		m_IsSolid(true)
	{
		va_list args;
		va_start(args, vertexCount);

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			m_Vertices[i] = va_arg(args, sf::Vector2f);
			m_Center += m_Vertices[i];
		}

		m_Center = m_Center / (float)m_VertexCount;

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			float mag = Math::Magnitude(m_Vertices[i] - m_Center);
			if (mag > m_Radius)
			{
				m_Radius = mag;
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
			context.DebugDrawer.AddLine(m_Vertices[i] + offset, m_Vertices[(i + 1) % m_VertexCount] + offset);
		}
	}

	bool Collider::CleanUp(Context& context)
	{
		context.CommandQueue.QueueMessage("Remove Collider", this);
		return false;
	}

	void Collider::HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		if (m_Handler)
		{
			m_Handler->HandleCollision(dt, contactPoint, correction, collider);
		}
	}

	void Collider::Update(float dt)
	{
		if (m_Handler)
		{
			m_Handler->Update(dt);
		}
	}

	void Collider::ApplyForce(sf::Vector2f force)
	{
		m_AffectedEntity->Accelerate(force / m_Mass);
	}

	void Collider::SetHandler(CollisionHandler* handler)
	{
		m_Handler = handler;
	}

	void Collider::SetMass(float mass)
	{
		m_Mass = mass;
	}

	void Collider::SetBounciness(float bounciness)
	{
		m_Bounciness = bounciness;
	}

	void Collider::SetFriction(float friction)
	{
		m_Friction = friction;
	}

	void Collider::SetIsSolid(bool isSolid)
	{
		m_IsSolid = isSolid;
	}

	UniquePointer<sf::Vector2f> Collider::GetVertices() const
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

	sf::Vector2f Collider::GetCenter() const
	{
		return m_Center + m_AffectedEntity->getPosition();
	}

	float Collider::GetMass() const
	{
		return m_Mass;
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

	const sf::Vector2f& Collider::GetVelocity() const
	{
		return m_AffectedEntity->GetVelocity();
	}

	float Collider::GetRadius() const
	{
		return m_Radius;
	}

	sf::Vector2f Collider::FarthestVertex(const sf::Vector2f& direction) const
	{
		sf::Vector2f vertex(0.0f, 0.0f);
		sf::Vector2f offset(0.0f, 0.0f);
		if (m_AffectedEntity)
		{
			offset = m_AffectedEntity->getPosition();
		}
		float magnitude = -99999999.0f;

		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			float mag = Math::Dot(direction, m_Vertices[i] + offset);
			if (mag > magnitude)
			{
				vertex = m_Vertices[i] + offset;
				magnitude = mag;
			}
		}

		return vertex;
	}
}