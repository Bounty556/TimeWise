#include "Rigidbody.h"

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity, bool isSolid, float bounciness, float friction) :
		Component(entity),
		m_IsSolid(isSolid),
		m_Bounciness(bounciness),
		m_Friction(friction),
		m_Collider(nullptr)
	{

	}

	void Rigidbody::HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		m_AffectedEntity->move(correction);
	}

	bool Rigidbody::IsSolid() const
	{
		return m_IsSolid;
	}

	float Rigidbody::GetBounciness() const
	{
		return m_Bounciness;
	}

	float Rigidbody::GetFriction() const
	{
		return m_Friction;
	}

	void Rigidbody::SetIsSolid(bool isSolid)
	{
		m_IsSolid = isSolid;
	}

	void Rigidbody::SetBounciness(float bounciness)
	{
		m_Bounciness = bounciness;
	}

	void Rigidbody::SetFriction(float friction)
	{
		m_Friction = friction;
	}

	void Rigidbody::SetCollider(Collider* collider)
	{
		m_Collider = collider;
		m_Collider->SetHandler(this);
	}

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}
}